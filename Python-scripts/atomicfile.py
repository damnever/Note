import os
import codecs
import tempfile
import shutil
import errno

# The following code is a modified version of `https://github.com/sashka/atomicfile`,
# the origin code is released under the MIT license.
umask = os.umask(0)
os.umask(umask)


def _maketemp(name, createmode=None):
    """
    Create a temporary file with the filename similar the given ``name``.
    The permission bits are copied from the original file or ``createmode``.
    Returns: the name of the temporary file.
    """
    d, fn = os.path.split(name)
    fd, tempname = tempfile.mkstemp(prefix=".%s-" % fn, dir=d)
    os.close(fd)

    # Temporary files are created with mode 0600, which is usually not
    # what we want. If the original file already exists, just copy its mode.
    # Otherwise, manually obey umask.
    try:
        st_mode = os.lstat(name).st_mode & 0o777
    except OSError as err:
        if err.errno != errno.ENOENT:
            raise
        st_mode = createmode
        if st_mode is None:
            st_mode = ~umask
        st_mode &= 0o666
    os.chmod(tempname, st_mode)

    return tempname


class AtomicFile(object):
    """
    Writeable file object that atomically writes a file.
    All writes will go to a temporary file.
    Call ``close()`` when you are done writing, and AtomicFile will rename
    the temporary copy to the original name, making the changes visible.
    If the object is destroyed without being closed, all your writes are
    discarded.
    If an ``encoding`` argument is specified, codecs.open will be called to open
    the file in the wanted encoding.
    """
    def __init__(self, name, mode="w+b", createmode=None, encoding=None):
        self.__name = name  # permanent name
        self._tempname = _maketemp(name, createmode=createmode)
        if 'a' in mode and os.path.isfile(name):
            shutil.copyfile(name, self._tempname)
        if encoding:
            self._fp = codecs.open(self._tempname, mode, encoding)
        else:
            self._fp = open(self._tempname, mode)

        # delegated methods
        self.write = self._fp.write
        self.fileno = self._fp.fileno

    def __enter__(self):
        return self

    def __exit__(self, exc_type, exc_value, exc_tb):
        if exc_type:
            return
        self.close()

    def close(self):
        if not self._fp.closed:
            self._fp.close()
            os.rename(self._tempname, self.__name)

    def discard(self):
        if not self._fp.closed:
            try:
                os.unlink(self._tempname)
            except OSError:
                pass
            self._fp.close()

    def __del__(self):
        if getattr(self, "_fp", None):  # constructor actually did something
            self.discard()

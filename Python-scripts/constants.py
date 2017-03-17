class Constants(dict):

    def __init__(self, *args, **kwargs):
        super(Constants, self).__init__(*args, **kwargs)

    def __setitem__(self, key, value):
        if key in self:
            raise RuntimeError('can not change value of "{}"'.format(key))
        super(Constants, self).__setitem__(key, value)
    __setattr__ = __setitem__

    def __getitem__(self, key):
        if key not in self:
            raise AttributeError('attribute "{}" does not exists'.format(key))
        return super(Constants, self).__getitem__(key)
    __getattr__ = __getitem__

    def __delitem__(self, name):
        raise RuntimeError('can not delete "{}"'.format(name))
    __delattr__ = __delitem__

    def contain_value(self, value):
        return value in self.itervalues()

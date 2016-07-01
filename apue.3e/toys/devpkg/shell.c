#include <stdarg.h>
#include "shell.h"
#include "dbg.h"


int Shell_exec(Shell tpl, ...)
{
    apr_pool_t *p = NULL;
    int rc = -1;
    apr_status_t rv = APR_SUCCESS;
    va_list ap;
    const char *key = NULL;
    const char *arg = NULL;
    int i = 0;
    int arg_count = 0;

    rv = apr_pool_create(&p, NULL);
    check(rv == APR_SUCCESS, "Failed to create pool.");

    va_start(ap, tpl);

    for (key = va_arg(ap, const char *); key != NULL; key = va_arg(ap, const char *)) {
        arg = va_arg(ap, const char *);

        for (i = 0; tpl.args[i] != NULL; ++i) {
            if (strcmp(tpl.args[i], key) == 0) {
                tpl.args[i] = arg;
                arg_count += 1;
                break;
            }
        }
    }
    check(arg_count == tpl.args_len, "Arguments number does not match.");

    rc = Shell_run(p, &tpl);
    apr_pool_destroy(p);
    va_end(ap);
    return rc;

error:
    if (p) apr_pool_destroy(p);
    return rc;
}


int Shell_run(apr_pool_t *p, Shell *cmd)
{
    apr_procattr_t *attr;
    apr_status_t rv;
    apr_proc_t newproc;

    rv = apr_procattr_create(&attr, p);
    check(rv == APR_SUCCESS, "Failed to create proc attr.");

    rv = apr_procattr_io_set(attr, APR_NO_PIPE, APR_NO_PIPE, APR_NO_PIPE);
    check(rv == APR_SUCCESS, "Failed to set IO of command.");

    rv = apr_procattr_dir_set(attr, cmd->dir);
    check(rv == APR_SUCCESS, "Failed to set root to %s", cmd->dir);

    rv = apr_procattr_cmdtype_set(attr, APR_PROGRAM_PATH);
    check(rv == APR_SUCCESS, "Failed to set cmd type.");

    rv = apr_proc_create(&newproc, cmd->exe, cmd->args, NULL, attr, p);
    check(rv == APR_SUCCESS, "Failed to run cmd.");

    rv = apr_proc_wait(&newproc, &cmd->exit_code, &cmd->exit_why, APR_WAIT);
    check(rv == APR_CHILD_DONE, "Failed to wait.");

    check(cmd->exit_code == 0, "%s exited badly.", cmd->exe);
    check(cmd->exit_why == APR_PROC_EXIT, "%s was killed or crushed.", cmd->exe);

    return 0;

error:
    return -1;
}


Shell CLEANUP_SH = {
    .dir = "/tmp",
    .exe = "rm",
    .args = {"rm", "-rf", "/tmp/pkg-build", "/tmp/pkg-src.tar.gz",
    "/tmp/pkg-src.tar.bz2", "/tmp/DEPENDS", NULL},
    .args_len = 0,
};

Shell GIT_SH = {
    .dir = "/tmp",
    .exe = "git",
    .args = {"git", "clone", "URL", "pkg-build", NULL},
    .args_len = 1,
};

Shell TAR_GZ_SH = {
    .dir = "/tmp/pkg-build/",
    .exe = "tar",
    .args = {"tar", "-xzf", "FILE", "--strip-components", "1", NULL},
    .args_len = 1,
};

Shell TAR_BZ2_SH = {
    .dir = "/tmp/pkg-build/",
    .exe = "tar",
    .args = {"tar", "-xjf", "FILE", "--strip-components", "1", NULL},
    .args_len = 1,
};

Shell CURL_SH = {
    .dir = "/tmp",
    .exe = "curl",
    .args = {"curl", "-L", "-o", "TARGET", "URL", NULL},
    .args_len = 2,
};

Shell CONFIGURE_SH = {
    .dir = "/tmp/pkg-build",
    .exe = "./configure",
    .args = {"./configure", "OPTS", NULL},
    .args_len = 1,
};

Shell MAKE_SH = {
    .dir = "/tmp/pkg-build",
    .exe = "make",
    .args = {"make", "OPTS", NULL},
    .args_len = 1,
};

Shell INSTALL_SH = {
    .dir = "/tmp/pkg-build",
    .exe = "sudo",
    .args = {"sudo", "make", "TARGET", NULL},
    .args_len = 1,
};

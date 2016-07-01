#ifndef _db_h_
#define _db_h_

#define DB_DIR "/usr/local/.devpkg/"
#define DB_FILE "/usr/local/.devpkg/db"


int DB_init();
int DB_list();
int DB_update(const char *url);
int DB_find(const char *url);


#endif

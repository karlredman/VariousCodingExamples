#include "MySQLWrapper.h"
#include <stdio.h>

MySQLWrapper::MySQLWrapper(char *user, char *password, char *db, char *host, unsigned short port) {
   this->user = user;
   this->password = password;
   this->db = db;
   this->host = host;
   this->port = port;
   setError(E_NONE);
   connect();
}

MySQLWrapper::~MySQLWrapper() {
   disconnect();
}

void MySQLWrapper::connect() {

   conn = mysql_init(NULL);       /* allocate, initialize connection handler */
   if (conn == NULL) {
      setError(E_INIT);
   }
   else if (mysql_real_connect (conn, host, user, password,
                           db, port, DEF_SOCKET_NAME, DEF_FLAGS) == NULL) {
      setError(E_CONN);
   }
}

void MySQLWrapper::disconnect() {
   if (conn) {
      mysql_close(conn);
   }
}

bool MySQLWrapper::query(char *stmt) {
   MYSQL_RES *res_set;
   unsigned int field_count;

   if (mysql_query (conn, stmt) != 0) {
      setError(E_QUERY);
      return false;
   }

   res_set = mysql_store_result (conn);
   if (res_set == NULL) {
      if (mysql_field_count (conn) > 0) {
         setError(E_RESULT);
         return false;
      }
   }
   else {
      /* process rows, then free the result set */
      processResultSet(conn, res_set);
      mysql_free_result(res_set);
   }

   return true;
}

void MySQLWrapper::print_dashes(MYSQL_RES *res_set) {
   MYSQL_FIELD             *field;
   unsigned int    i, j;

   mysql_field_seek (res_set, 0);
   fputc ('+', stdout);
   for (i = 0; i < mysql_num_fields (res_set); i++) {
      field = mysql_fetch_field (res_set);
      for (j = 0; j < field->max_length + 2; j++) {
         fputc ('-', stdout);
      }
      fputc ('+', stdout);
   }
   fputc ('\n', stdout);
}

void MySQLWrapper::processResultSet(MYSQL *conn, MYSQL_RES *res_set) {
   MYSQL_FIELD             *field;
   MYSQL_ROW               row;
   unsigned int    i, col_len;

   /* determine column display widths */
   mysql_field_seek (res_set, 0);
   for (i = 0; i < mysql_num_fields (res_set); i++) {
      field = mysql_fetch_field (res_set);
      col_len = strlen (field->name);
      if (col_len < field->max_length)
         col_len = field->max_length;
      if (col_len < 4 && !IS_NOT_NULL (field->flags))
         col_len = 4;    /* 4 = length of the word "NULL" */
      field->max_length = col_len;    /* reset column info */
   }

   print_dashes (res_set);
   fputc ('|', stdout);
   mysql_field_seek (res_set, 0);
   for (i = 0; i < mysql_num_fields (res_set); i++) {
      field = mysql_fetch_field (res_set);
      printf (" %-*s |", field->max_length, field->name);
   }
   fputc ('\n', stdout);
   print_dashes (res_set);

   while ((row = mysql_fetch_row (res_set)) != NULL) {
      mysql_field_seek (res_set, 0);
      fputc ('|', stdout);
      for (i = 0; i < mysql_num_fields (res_set); i++) {
         field = mysql_fetch_field (res_set);
         if (row[i] == NULL)
            printf (" %-*s |", field->max_length, "NULL");
         else if (IS_NUM (field->type))
            printf (" %*s |", field->max_length, row[i]);
         else
            printf (" %-*s |", field->max_length, row[i]);
      }
      fputc ('\n', stdout);
   }
   print_dashes (res_set);
   printf ("%lu rows returned\n", (unsigned long) mysql_num_rows (res_set));
}

void MySQLWrapper::setError(int err) {
   errno = err;
}

int MySQLWrapper::getError() const {
   return errno;
}

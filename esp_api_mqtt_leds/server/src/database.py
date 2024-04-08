import sqlite3


class SqliteDB:
    def __init__(self):
        self.__db_name = '../local.db'
        self.__connection = sqlite3.connect(self.__db_name)
    # def __enter__(self):
    #     return self.__connection
    #
    # def __exit__(self, exc_type, exc_val, exc_tb):
    #     self.close_connection()
    #     return

    def execute_query(self, query_statement: str, args=None) -> list:
        cursor = self.__connection.cursor()
        try:
            if args:
                cursor.executemany(query_statement, args)
            else:
                cursor.execute(query_statement)
            self.__connection.commit()
            return cursor.fetchall()
        except sqlite3.Error as e:
            print("ERROR:   ", str(e))
            return []

    def close_connection(self):
        self.__connection.close()




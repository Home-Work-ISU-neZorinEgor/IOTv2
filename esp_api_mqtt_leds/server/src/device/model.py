from src.database import SqliteDB


def create_device_table(engine: SqliteDB):
    stmt = ("""
            CREATE TABLE IF NOT EXIST Devices(
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            device_name TEXT NOT NULL, 
            mac_address TEXT NOT NULL,
            user_id INTEGER,
            FOREIGN KEY (user_id) REFERENCES Users(id)
            )""")
    engine.execute_query(stmt)

from src.database import SqliteDB


def create_color_leds_table(engine: SqliteDB):
    stmt = """
            CREATE TABLE IF NOT EXISTS Colors(
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            color_series TEXT NOT NULL,
            user_id INTEGER,
            FOREIGN KEY (user_id) REFERENCES Users(id)
            )
        """
    engine.execute_query(stmt)

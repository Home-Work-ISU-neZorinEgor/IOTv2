from src.database import SqliteDB


def create_user_table(engine: SqliteDB):
    stmt = """
        CREATE TABLE IF NOT EXISTS Users (
            username TEXT UNIQUE NOT NULL,
            password TEXT NOT NULL
        )
    """
    engine.execute_query(stmt)
    engine.close_connection()
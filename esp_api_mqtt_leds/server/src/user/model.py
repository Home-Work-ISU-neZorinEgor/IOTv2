from server.src.database import engine
from sqlalchemy import Table, Column, MetaData, String, Integer

user_meta_data = MetaData()

user_table = Table(
    'users',
    user_meta_data,
    Column('id', Integer, autoincrement=True),
    Column('username', String(length=50), nullable=False),
    Column('password', String(length=50), nullable=False),
)


def create_user_table():
    user_meta_data.drop_all(engine)
    user_meta_data.create_all(engine)

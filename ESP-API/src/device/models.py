from sqlalchemy import text, Table, Column, String, MetaData, Integer, Float

# Data about tables created on the python side
meta_data = MetaData()

temperature = Table(
    'temperature',
    meta_data,
    Column('id', Integer, primary_key=True, autoincrement=True),
    Column('value', Float, nullable=False),
    Column('location', String(length=50), nullable=False)
)

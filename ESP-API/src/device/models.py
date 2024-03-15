from sqlalchemy import Table, Column, String, MetaData, Float, Integer

# Data about tables created on the python side
meta_data = MetaData()

temperature = Table(
    'device',
    meta_data,
    Column('id', Integer, primary_key=True),
    Column('value', Float, nullable=False),
    Column('location', String(length=50), nullable=False)
)

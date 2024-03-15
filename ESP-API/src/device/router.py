from fastapi import APIRouter
from sqlalchemy import text
from src.database.database import engine
from src.device.models import meta_data
from src.device.schemas import GetTemperature


temperature_router = APIRouter()


def create_tables():
    meta_data.drop_all(engine)
    meta_data.create_all(engine)


@temperature_router.post('/all')
def insert_data(value, location):
    with engine.connect() as conn:
        stmt = text('''
            INSERT INTO device (value, location) VALUES (:value, :location);
        ''')
        conn.execute(stmt, {'value': value, 'location': location})
        conn.commit()


@temperature_router.get('/all')
def get_data(location):
    with engine.connect() as conn:
        stmt = '''
            SELECT * FROM `device` WHERE `location` = :location;
        '''
        resource = conn.execute(text(stmt), {'location': location})
        conn.commit()
        return [GetTemperature(id=i[0], value=i[1], location=i[2]) for i in list(resource)]


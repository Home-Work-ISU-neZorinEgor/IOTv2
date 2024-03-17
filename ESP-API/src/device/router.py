from fastapi import APIRouter, status
from fastapi.responses import JSONResponse
from fastapi.exceptions import HTTPException
from src.device.models import meta_data
from src.database.engine import engine
from sqlalchemy import text
from src.device.schemas import GetTemperature

temperature_router = APIRouter()


def create_temperature_table():
    meta_data.drop_all(engine)
    meta_data.create_all(engine)


@temperature_router.get('/get_temperatures', response_model=GetTemperature)
def get_temperatures_by_location(location: str) -> GetTemperature:
    with engine.connect() as conn:
        stmt = '''
            SELECT value FROM `temperature` WHERE `location` = :location;
        '''
        resource = conn.execute(text(stmt), {'location': location})
        conn.commit()
        lst = list()
        for i in list(resource):
            lst.append(*i)
        if len(lst) == 0:
            raise HTTPException(status_code=status.HTTP_404_NOT_FOUND, detail={
                'ok': False,
                'detail': 'Value by this location not exist'})
        return GetTemperature(values=lst, location=location)


@temperature_router.post('/add_temperatures')
def save_temperatures(value: float, location: str) -> JSONResponse:
    with engine.connect() as conn:
        stmt = text('''
            INSERT INTO `temperature` (value, location) VALUES (:value, :location);
        ''')
        conn.execute(stmt, {'value': value, 'location': location})
        conn.commit()
    return JSONResponse(status_code=status.HTTP_200_OK, content={'ok': True})

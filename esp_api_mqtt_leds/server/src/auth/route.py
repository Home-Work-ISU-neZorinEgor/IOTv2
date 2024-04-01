import secrets

from fastapi import APIRouter, Depends
from server.src.auth.exceptions import not_auth_exception
from fastapi.security import HTTPBasic, HTTPBasicCredentials

from typing import Annotated

auth_router = APIRouter(prefix='/auth')
security = HTTPBasic()

fake_db = {'admin': 'admin', 'test': 123}


def check_auth(credentials: Annotated[HTTPBasicCredentials, Depends(security)]):
    if credentials.username not in fake_db:
        raise not_auth_exception
    if not secrets.compare_digest(fake_db[credentials.username].encode('utf-8'),
                                  credentials.password.encode('utf-8')):
        raise not_auth_exception
    return credentials.username


@auth_router.get('/whoami')
def check_credentials(credentials: str = Depends(check_auth)):
    return f'Hi, {credentials}'





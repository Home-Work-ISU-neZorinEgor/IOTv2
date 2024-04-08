from fastapi import APIRouter, Depends
from fastapi.security import HTTPBasic, HTTPBasicCredentials
from fastapi.responses import JSONResponse

from src.auth.exceptions import unauthorized_exception, exists_suer
from src.database import SqliteDB
from src.auth.scheme import UserResponse, FullUserInfo

from typing import Annotated

auth_router = APIRouter(prefix="/auth", tags=['HttpBasicAuth'])
security = HTTPBasic()


def check_auth(credentials: Annotated[HTTPBasicCredentials, Depends(security)]) -> FullUserInfo:
    engine = SqliteDB()
    try:
        user = engine.execute_query(f"""
            SELECT * FROM Users WHERE username='{credentials.username}' AND password='{credentials.password}'
                    """)
        if user:
            return FullUserInfo(id=user[0][0], username=user[0][1], password=user[0][2])
        raise unauthorized_exception
    finally:
        engine.close_connection()


@auth_router.get("/check/whoami", response_model=FullUserInfo)
def whoami(auth: FullUserInfo = Depends(check_auth)):
    return auth


@auth_router.post("/register")
def register(user: UserResponse):
    engine = SqliteDB()
    try:
        exist_user = engine.execute_query(f"SELECT * FROM Users WHERE username='{user.username}'")
        if len(exist_user) != 0:
            raise exists_suer
        else:
            stmt = "INSERT INTO Users(username, password) VALUES (?, ?)"
            args = [(user.username, user.password)]
            engine.execute_query(stmt, args)
            return JSONResponse(
                {
                    "ok": True,
                    "detail": f"Register user {user.username} successfully."
                })
    finally:
        engine.close_connection()

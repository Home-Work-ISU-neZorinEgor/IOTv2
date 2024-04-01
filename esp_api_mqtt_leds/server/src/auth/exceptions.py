from fastapi import status
from fastapi.responses import JSONResponse
from fastapi.exceptions import HTTPException

not_auth_exception = HTTPException(status_code=status.HTTP_401_UNAUTHORIZED,
                                   detail={'message': 'Invalid username or password', 'recommend': 'register on ...'})


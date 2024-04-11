from fastapi import HTTPException, status

unauthorized_exception = HTTPException(status_code=status.HTTP_401_UNAUTHORIZED,
                                       detail={
                                           "ok": False,
                                           "message": "Invalid username or password"
                                       })

exists_suer = HTTPException(
                status_code=status.HTTP_409_CONFLICT, detail={
                    "ok": False,
                    "message": "User with name already exist."
                })

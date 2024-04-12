from pydantic import BaseModel


class DeviceRegister(BaseModel):
    name: str
    mac_addr: str


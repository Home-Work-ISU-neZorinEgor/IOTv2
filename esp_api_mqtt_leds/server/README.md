# Project tree structure
```
.
├── Dockerfile
├── local.db
├── README.md
├── requirements.txt
└── src
    ├── auth
    │   ├── exceptions.py
    │   ├── model.py
    │   ├── router.py
    │   └── scheme.py
    ├── pixels
    │   ├── model.py
    │   ├── router.py
    │   └── scheme.py
    ├── database.py
    └── main.py
```
# Run serer 
1. ```bash
   docker build . -t app:1.0
    ```

2. ```bash
    docker run -d --rm -p 8888:5000 app:1.0 
   ```
1. ```bash
   docker build . -t app:1.0
    ```

2. ```bash
    docker run -d --rm -p 8888:5000 app:1.0 
    ```
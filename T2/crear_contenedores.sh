for i in {1..10}
do
    CONTAINER_NAME=$(openssl rand -hex 6)
    docker run -d --name "container_$CONTAINER_NAME" alpine
    echo "Contenedor creado: container_$CONTAINER_NAME"
done
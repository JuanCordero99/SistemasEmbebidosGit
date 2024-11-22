<?php
require_once('helper.php'); // Incluye el archivo de funciones

header("Content-Type: application/json"); // Indica que la respuesta es JSON
header("Access-Control-Allow-Origin: *"); // Permite el acceso desde cualquier origen

// Conecta a la base de datos
$mysqli = conectar();

// Realiza la consulta
$query = "SELECT * FROM sensor_pir";
$result = $mysqli->query($query);

// Verifica si la consulta fue exitosa
if ($result) {
    $data = [];

    // Itera sobre los resultados y los agrega al arreglo
    while ($row = $result->fetch_assoc()) {
        $data[] = $row;
    }

    // Devuelve los resultados en formato JSON
    echo json_encode(['status' => 'success', 'data' => $data]);
} else {
    // En caso de error en la consulta
    echo json_encode(['status' => 'Error No data']);
}

// Cierra la conexión
desconectar();
?>

<?php
require_once ('helper.php'); // Incluye el archivo de funciones

header("Content-Type: application/json"); // Indica que la respuesta es JSON
header("Access-Control-Allow-Origin: *"); // Permite el acceso desde cualquier origen

// Conecta a la base de datos
$mysqli = conectar();

// Obtiene los datos JSON enviados
$jsonData = file_get_contents('php://input');
$data = json_decode($jsonData, true);

$value = $data['value'] ?? null; // Obtiene el valor del JSON

if ($value !== null) {
    // Inserta directamente sin preparación (evita medidas de seguridad avanzadas)
    $query = "INSERT INTO iot (value) VALUES ('$value')";
    if ($mysqli->query($query)) {
        echo json_encode(['status' => 'Data received']);
    } else {
        echo json_encode(['status' => 'Error inserting data']);
    }
} else {
    echo json_encode(['status' => 'No data']);
}

// Cierra la conexión
desconectar();
?>

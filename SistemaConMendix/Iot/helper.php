<?php

// FUNCIONES DE BIBLIOTECA (helper.php)
function conectar() {
	$server   = "localhost";
	$user     = "corjua228";
	$password = "csj@2023371024";
	$db       = "bd_awos";
	$mysqli   = new mysqli( $server, $user, $password, $db );

	return $mysqli;
}

function desconectar() {
	global $mysqli;
	$mysqli->close();
}

function query( $sql ) {
	global $mysqli;
	$rs = $mysqli->query( $sql ) or die( $mysqli->error );
	return $rs;
}

?>
#include <stdio.h>
#include <stdlib.h>
#include <mysql/mysql.h>
#include <string.h>

int main(int argc, char **argv) {
	MYSQL *conn;
	int err;
	MYSQL_RES *result;
	MYSQL_ROW row;
	
	conn = mysql_init(NULL);
	
	if (conn == NULL) {
		printf("Error creando la conexion: %u %s\n", mysql_errno(conn), mysql_error(conn));
		exit(1);
	}
	
	conn = mysql_real_connect(conn, "localhost", "root", "mysql", "GameDB", 0, NULL, 0);
	if (conn == NULL) {
		printf("Error inicializando la conexionn: %u %s\n", mysql_errno(conn), mysql_error(conn));
		exit(1);
	}
	
	char query[] = "SELECT `Match`.match_id, `Match`.finish_time, `Match`.duration, Player.username AS winner "
		"FROM `Match` "
		"JOIN Player_Match ON `Match`.match_id = Player_Match.match_id "
		"JOIN Player ON `Match`.winner_id = Player.player_id "
		"WHERE Player_Match.player_id = 1;";
	
	err = mysql_query(conn, query);
	if (err != 0) {
		printf("Error en la consulta SQL: %u %s\n", mysql_errno(conn), mysql_error(conn));
		exit(1);
	}
	
	result = mysql_store_result(conn);
	if (result == NULL) {
		printf("No se pudo obtener el resultado de la consulta: %u %s\n", mysql_errno(conn), mysql_error(conn));
		exit(1);
	}
	printf("Resultados del partido:\n");
	while ((row = mysql_fetch_row(result)) != NULL) {
		printf("ID del partido: %s, Hora fin: %s, Duracion: %s minutos, Ganador: %s\n",
			   row[0], row[1], row[2], row[3]);
	}
	
	
	mysql_free_result(result);
	mysql_close(conn);
	
	return 0;
}


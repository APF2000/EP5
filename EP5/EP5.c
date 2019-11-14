/*****************************************************************/
/**                                                           	**/
/**   JosÃ© Lucas De Melo Costa          Numero USP: 07335100 	**/
/**   Luiz Guilherme Kasputis Zanini     Numero USP: 10773116 	**/
/**   Arthur Pires Da Fonseca            Numero USP: 10773096 	**/
/**   ExercÃ­cio-Programa 05                                   	**/
/**   Professor: Carlos Eduardo Ferreira                      	**/
/**   Turma: 01                                               	**/
/**                                                           	**/
/*****************************************************************/

#include "../robot_fight.h"
static Direction direcao;


Action processTurn(Grid *g, Position p, int turnsLeft);
void prepareGame(Grid *g, Position p, int turnCount);

/*VariÃ¡veis para armazenas informaÃ§Ãµes de turnos passados*/
int ultimo_cpx, ultimo_cpy;
int anterior_defesa;
int direcoes[6];


static int control_dir;

/*Verifica se a posiÃ§Ã£o estÃ¡ vÃ¡lida*/
int valid(Position p, int m, int n, Grid *g) {
	return ((p.x >= 0 && p.x < m && p.y >= 0 && p.y < n));
}

int valid2(Position p, int m, int n, Grid *g) {
	return ((p.x >= 0 && p.x < m && p.y >= 0 && p.y < n) && (g->map[p.x][p.y].type == NONE));
}

void prepareGame(Grid *g, Position p, int turnCount) {
	/* NOSSO ROBO TEM A FURIA E O PODER */
}

/*Dada uma direcao inicial e uma direcao final, ve qual
o menor numero de viradas sao necessarias*/
int quickTurn(int ini, int end) {
	int i, j;
	for(i = ini, j = 0; i != end; i = (i+1)%6, j++)
		if (i >= 6) i-= 6;
	if (j > 3) j = 6-j;
	return j;
}

/*Dada uma direcao inicial e uma direcao final, ve
para qual lado virando eh mais rapido de se chegar*/
Action fastTurn(int ini, int end) {
	int dif = end-ini;
	if((dif <= 3 && dif >= 0) || (dif <= -3))
		return TURN_RIGHT;
	else
		return TURN_LEFT;
}

int isControlPoint(Grid *g, Position p) {
	return (g->map[p.x][p.y].isControlPoint);
}


/*Dado uma posicao, checa se para alguma direcao
existe um control point, e retorna qual direcao esta
o mais perto, contando giradas necessÃ¡rias*/
int searchNearestControl(Grid *g, Position p, Robot *r) {
	int i, min = 500, best_dir = 0, cont;
	for(i = 0; i < 6; i++) {
		/*Conta para chegar o numero de viradas necessarias
		ja que elas gastam um turno*/
		cont = 1 + quickTurn(r->dir, i);
		Position s = getNeighbor(p,i);
		while(valid(s, g->m, g->n, g)) {
			if(isControlPoint(g,s) && s.x != ultimo_cpx && s.y != ultimo_cpy && g->map[s.x][s.y].type != ROBOT) {
				if(cont < min) {
					min = cont;
					best_dir = i;
					break;
				}
			}
			cont++;
			s = getNeighbor(s, i);
		}
	}

	/*Nao existe control points no mapa*/
	if (min == 500)
		return -1;

	else
		return best_dir;
}

/*Verifica se a trajetoria do projetil irÃ¡ atingir o robÃ´*/
int traca_colisao(Grid *g, Position projectile, Position robot, Direction dir){

	Position s = projectile;
	int valido, achei = 0;

	valido = valid(s, g->m, g->n, g);

	while(valido == 1 && achei == 0){
		if(s.x == robot.x && s.y == robot.y)
			achei = 1;
		s = getNeighbor(s, dir);
		valido = valid(s, g->m, g->n, g);
	}
return achei;
}


/*Se estiver havendo um conflito, atacamos os robÃ´s vulnerÃ¡veis*/
int ChecaConflito(Grid *g, Position inimigo, int direcao){
	Position aux;
	aux.x = inimigo.x;
	aux.y = inimigo.y;

	int i;
	Tile auxtile;

	int cont=0;//Contador para saber se o inimigo vai receber tiro em <2 distÃ¢ncia


	for(i=0;i<6;i++){
		aux = getNeighbor(inimigo, i);

		while( valid(aux, g->m, g->n, g)   &&   cont<3  &&   i!=direcao){
			/*Se ele tiver dando tiro ou recebendo tiro de uma direÃ§Ã£o diferente do nosso robo, ele manda bala*/
			auxtile = g->map[aux.x][aux.y];
			if( auxtile.type == PROJECTILE && g->map[aux.x][aux.y].object.projectile.ownerIndex == g->map[inimigo.x][inimigo.y].object.robot.index ){
				return 1;
			}

			cont++;
			aux = getNeighbor(aux, i);
		}
		aux = inimigo;
		cont=0;
	}
	return 0;
}

int findAtack(Grid *g, Position atual){
	int i;
	Position auxpos;

	for(i = 0; i < 6; i++){

		Tile auxtile = g->map[atual.x][atual.y];
		auxpos = getNeighbor(atual, i);

		while(valid(auxpos, g->m, g->n, g)){

	  		auxtile = g->map[auxpos.x][auxpos.y];

	  	  	//Se tem hexÃ¡gonos na direÃ§Ã£o i
		    	if( auxtile.type == ROBOT ){

		    		//Aqui ele verifica se o robo estÃ¡ em conflito se ele tiver ele devolve na funÃ§Ã£o a direcao pra atirar
		      		if(ChecaConflito(g ,auxpos, i))
		      			return i;

				break;
		    	}
	    	auxpos = getNeighbor(auxpos, i);

		}
	  }
  return -1;
}


Action BestTurnAtack(Grid *g, Position p, Direction ataque){
	Direction direcao = g->map[p.x][p.y].object.robot.dir;

	// Verificar Se Ã© pra atacar ou girar
	if(direcao == ataque)
		return SHOOT_CENTER;
	if( (direcao+1)%6 == ataque)
		return SHOOT_RIGHT;
	if( (direcao+5)%6 == ataque)
		return SHOOT_LEFT;
	if( (direcao+2)%6 == ataque)
		return TURN_RIGHT;
	if( (direcao+4)%6 == ataque)
		return TURN_LEFT;

	return TURN_LEFT;
}

/*Determina se o robÃ´ estÃ¡ ou nÃ£o em risco de ser atingido*/
int acha_projetil(Grid *g, Position p, int i) {
	int achei = 0, valido, acabou = 0;
	Direction dir_check;

	Position s = p;
	valido = valid(s, g->m, g->n, g);

	while(valido == 1 && acabou == 0) {
		if(g->map[s.x][s.y].type == PROJECTILE) {
			dir_check = g->map[s.x][s.y].object.projectile.dir;

			if(traca_colisao(g, s, p, dir_check) == 1){
				direcao = i;
				achei = 1;
				acabou = 1;
			}else{
				acabou = 1;
			}
		}
		s = getNeighbor(s, i);
		valido = valid(s, g->m, g->n, g);
	}
return achei;
}

int verifica_ao_lado(Grid *g, Position p){
	Position vizin;
	int i;

	for(i = 0;  i < 6; i++){
		vizin = getNeighbor(p, i);
		if(g->map[vizin.x][vizin.y].type == ROBOT ){
				return i;
		}
	}
return -1;
}

int detecta_ameaca(Grid *g, Position p, int *direcoes){

	int i, cont = 0;
	for(i = 0; i < 6; i++){
		if(acha_projetil(g, p, i) == 1){
			direcoes[direcao] = 1;
			cont++;
		}
	}
return cont;
}

Action bestTurn(Direction from, Direction to) {
	if(((6 + from - to) % 6) < 3) return TURN_LEFT;
	else return TURN_RIGHT;
}



Action sebo_nas_canela(Grid *g, Position p){

	Position vizin;
	Robot *r = &g->map[p.x][p.y].object.robot;
	int i;

	ultimo_cpx = p.x;
	ultimo_cpy = p.y;

	if(direcoes[r->dir] == 0 && direcoes[(r->dir + 3) % 6] == 0 ){
		vizin = getNeighbor(p, r->dir);
		if(valid2(vizin,g->m, g->n, g) == 1){
			return WALK;
		}
	}

	for(i = 0; i < 6; i++){
		if(direcoes[i] == 0 && direcoes[(i + 3) % 6] == 0 ){
			if((r->dir + 1) % 6 == i){
				return TURN_RIGHT;
			}

			if((r->dir + 5) % 6 == i)
				return TURN_LEFT;

			return bestTurn(r->dir, i);
		}
	}
vizin = getNeighbor(p, r->dir);
if(valid2(vizin,g->m, g->n, g) == 1){
	return WALK;
}
return TURN_RIGHT;
}

int DefesaRoboDistante(Grid *g, Position atual){
    Position aux;
    aux.x=atual.x-1;
    aux.y=atual.y-2;

    if(valid(aux, g->m, g->n, g)){
        if(g->map[aux.x][aux.y].type == ROBOT && g->map[aux.x][aux.y].object.robot.dir == 4)
            return TOP_LEFT;
        // Caso contrario ele nem retorna
    }

    aux.x=atual.x;
    aux.y=atual.y-2;

    if(valid(aux, g->m, g->n, g)){
        if(g->map[aux.x][aux.y].type == ROBOT && g->map[aux.x][aux.y].object.robot.dir == 4)
            return TOP_RIGHT;
        if(g->map[aux.x][aux.y].type == ROBOT && g->map[aux.x][aux.y].object.robot.dir == 5)
            return TOP_LEFT;
        // Caso contrario ele nem retorna
    }

    aux.x=atual.x+1;
    aux.y=atual.y-2;

    if(valid(aux, g->m, g->n, g)){
        if(g->map[aux.x][aux.y].type == ROBOT && g->map[aux.x][aux.y].object.robot.dir == 5)
            return TOP_RIGHT;

    }

    aux.x=atual.x+2;
    aux.y=atual.y-1;

    if(valid(aux, g->m, g->n, g)){
        if(g->map[aux.x][aux.y].type == ROBOT && g->map[aux.x][aux.y].object.robot.dir == 0)
            return TOP_RIGHT;
        if(g->map[aux.x][aux.y].type == ROBOT && g->map[aux.x][aux.y].object.robot.dir == 5)
            return RIGHT;

    }

    aux.x=atual.x+2;
    aux.y=atual.y;

    if(valid(aux, g->m, g->n, g)){
        if(g->map[aux.x][aux.y].type == ROBOT && g->map[aux.x][aux.y].object.robot.dir == 0)
            return RIGHT;
    }

    aux.x=atual.x+2;
    aux.y=atual.y+1;

    if(valid(aux, g->m, g->n, g)){
        if(g->map[aux.x][aux.y].type == ROBOT && g->map[aux.x][aux.y].object.robot.dir == 0)
            return RIGHT;
        if(g->map[aux.x][aux.y].type == ROBOT && g->map[aux.x][aux.y].object.robot.dir == 1)
            return BOTTOM_RIGHT;

    }

    aux.x=atual.x+1;
    aux.y=atual.y+2;

    if(valid(aux, g->m, g->n, g)){
        if(g->map[aux.x][aux.y].type == ROBOT && g->map[aux.x][aux.y].object.robot.dir == 1)
            return BOTTOM_RIGHT;
    }

    aux.x=atual.x;
    aux.y=atual.y+2;

    if(valid(aux, g->m, g->n, g)){
        if(g->map[aux.x][aux.y].type == ROBOT && g->map[aux.x][aux.y].object.robot.dir == 2)
            return BOTTOM_RIGHT;
        if(g->map[aux.x][aux.y].type == ROBOT && g->map[aux.x][aux.y].object.robot.dir == 1)
            return BOTTOM_LEFT;
    }

    aux.x=atual.x-1;
    aux.y=atual.y+2;

    if(valid(aux, g->m, g->n, g)){
        if(g->map[aux.x][aux.y].type == ROBOT && g->map[aux.x][aux.y].object.robot.dir == 2)
            return BOTTOM_LEFT;
    }

    aux.x=atual.x-1;
    aux.y=atual.y+1;

    if(valid(aux, g->m, g->n, g)){
        if(g->map[aux.x][aux.y].type == ROBOT && g->map[aux.x][aux.y].object.robot.dir == 3)
            return BOTTOM_LEFT;
        if(g->map[aux.x][aux.y].type == ROBOT && g->map[aux.x][aux.y].object.robot.dir == 2)
            return LEFT;
    }

    aux.x=atual.x-2;
    aux.y=atual.y;

    if(valid(aux, g->m, g->n, g)){
        if(g->map[aux.x][aux.y].type == ROBOT && g->map[aux.x][aux.y].object.robot.dir == 3)
            return LEFT;
    }

    aux.x=atual.x-1;
    aux.y=atual.y-1;

    if(valid(aux, g->m, g->n, g)){
        if(g->map[aux.x][aux.y].type == ROBOT && g->map[aux.x][aux.y].object.robot.dir == 3)
            return TOP_LEFT;
        if(g->map[aux.x][aux.y].type == ROBOT && g->map[aux.x][aux.y].object.robot.dir == 4)
            return LEFT;
    }

    return -1;
}

Action BestTurnDefesa(int acao, Grid *g, Position p){
    Robot *r = &g->map[p.x][p.y].object.robot;
    int direcao = r->dir, obst = r->obstacles;

    if( direcao == acao)
        return SHOOT_CENTER;
    if((direcao+5)%6 == acao)
        return SHOOT_LEFT;
    if((direcao+7)%6 == acao)
        return SHOOT_RIGHT;
    if( obst != 0){
        if((direcao+2)%6 == acao)
            return OBSTACLE_RIGHT;
        if((direcao+3)%6 == acao)
            return OBSTACLE_CENTER;
        if((direcao+4)%6 == acao)
            return OBSTACLE_LEFT;
    }
    return sebo_nas_canela(g ,p);
}

Action processTurn(Grid *g, Position p, int turnsLeft) {
	int i, j, ameacas = 0, dir_ameaca = -1, ataque = -1, robo_ao_lado = -1, ModoDefesa=-1;
	Position s, neighbor;
	Action aux;
	Robot *r = &g->map[p.x][p.y].object.robot;

	for(i = 0; i < 6; i++)
		direcoes[i] = 0;

	if(turnsLeft == 50)
		anterior_defesa = -1;


	/*Se estiver em cima de um control point, SCORE TIME*/
	if(isControlPoint(g,p)){

		ameacas = detecta_ameaca(g, p, direcoes);

		robo_ao_lado = verifica_ao_lado(g, p);


		if(robo_ao_lado != -1){
			direcoes[robo_ao_lado] = 1;
			return sebo_nas_canela(g, p);
		}



		if(ameacas == 1){

			for(i = 0; i < 6 && dir_ameaca == -1; i++){
				if(direcoes[i] == 1){
					dir_ameaca = i;
				}
			}

			if((6 + (r->dir - dir_ameaca)) % 6 == 3){

				neighbor = getNeighbor(p, dir_ameaca);

				if(r->obstacles != 0 && g->map[neighbor.x][neighbor.y].type != BLOCK)
					return OBSTACLE_CENTER;
				return STAND;
			}

			if(((r->dir + 2) % 6) == dir_ameaca){

				neighbor = getNeighbor(p, dir_ameaca);

				if(r->obstacles != 0 && g->map[neighbor.x][neighbor.y].type != BLOCK)
					return OBSTACLE_RIGHT;
				return STAND;
			}

			if(((r->dir + 4) % 6) == dir_ameaca){

				neighbor = getNeighbor(p, dir_ameaca);

				if(r->obstacles != 0 && g->map[neighbor.x][neighbor.y].type != BLOCK)
					return OBSTACLE_LEFT;
				return STAND;
			}

			return bestTurn((r->dir + 3) % 6, dir_ameaca);
		}else{
			/*Muitas ameaÃ§as*/
			if(ameacas != 0){
				return sebo_nas_canela(g, p);
			}else{

				ataque = findAtack(g, p);

				//O modo de defesa entra quando nÃ£o existe projetils entrando na direcao
                ModoDefesa = DefesaRoboDistante(g, p);

                if(ModoDefesa != -1){
					if(ModoDefesa != anterior_defesa){
						anterior_defesa = ModoDefesa;
						return BestTurnDefesa(ModoDefesa, g, p);
					}
                }

				if(ataque != -1){
					// Preciso saber se o ataque Ã© VALIDO e eu tenho q girar ou atacar
					return BestTurnAtack(g, p, ataque);

				}
			}
		return STAND;
		}
	}else {


		/*procura algum control point em alguam direcao do robo*/
		control_dir = searchNearestControl(g, p, r);
		/*Caso em nenhuma direcao tem um control point livre
		andar em uma direcao valida, ou comeca a virar para uma direcao valida*/
		if (control_dir == -1) {
			for(i = r->dir, j = 0; j < 6; i++,j++){
				if (i >= 6) i-=6;
				s = getNeighbor(p,i);
				if(valid(s, g->m, g->n, g)) {
					if(i == r->dir) {
						return WALK;
					}
					else {
						aux = fastTurn(r->dir, control_dir);

						if(aux == TURN_LEFT){
							neighbor = getNeighbor(p, (r->dir + 5) % 6);
							if(valid2(neighbor, g->m, g->n, g)){

								return aux;
							}

							neighbor = getNeighbor(p, r->dir);
							if(valid2(neighbor, g->m, g->n, g))
								return WALK;
							return TURN_RIGHT;
						}

						if(aux == TURN_RIGHT){
							neighbor = getNeighbor(p, (r->dir + 1) % 6);
							if(valid2(neighbor, g->m, g->n, g)){
								return aux;
							}

							neighbor = getNeighbor(p, r->dir);
							if(valid2(neighbor, g->m, g->n, g))
								return WALK;
							return TURN_LEFT;
						}
					}
				}
			}
			/*Se nenhuma posicao em volta eh valida, SAD TIME*/
			return STAND;
		}
		/*Se encontrou um control point em alguma direcao,
		 comeca a virar e andar em sua direcao*/
		else if(control_dir == r->dir){
			neighbor = getNeighbor(p, r->dir);
			if(valid2(neighbor, g->m, g->n, g))
				return WALK;
			return TURN_RIGHT;
		}
		else {
			aux = fastTurn(r->dir, control_dir);

			if(aux == TURN_LEFT){
				neighbor = getNeighbor(p, (r->dir + 5) % 6);
				if(valid2(neighbor, g->m, g->n, g)){

					return aux;
				}

				neighbor = getNeighbor(p, r->dir);
				if(valid2(neighbor, g->m, g->n, g))
					return WALK;
				return TURN_RIGHT;
			}

			if(aux == TURN_RIGHT){
				neighbor = getNeighbor(p, (r->dir + 1) % 6);
				if(valid2(neighbor, g->m, g->n, g)){
					return aux;
				}

				neighbor = getNeighbor(p, r->dir);
				if(valid2(neighbor, g->m, g->n, g))
					return WALK;
				return TURN_LEFT;
			}
		}
	}
return STAND;
}

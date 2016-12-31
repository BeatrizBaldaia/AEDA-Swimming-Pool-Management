#ifndef SRC_POOLMENU_H_
#define SRC_POOLMENU_H_

#include "Menu.h"

enum OrderBy {
	ID, NAME, NUMUSES, GIVENLESSONS, ASSLESSONS
};

class Pool;

/* POOL MENU */
/**
 * cria menus (� derivada da class Menu).
 */
class PoolMenu: public Menu {
public:
	/**
	 * Construtor de um menu.
	 * @param pool
	 */
	PoolMenu(Pool & pool);

private:
	/**
	 * refer�ncia � pool (onde � guardada toda a informa��o) para depois ser passada para as outras classes.
	 */
	Pool & pool;
};

/**
 * Sele��o do Menu referente � adi��o de um cliente � base de dados.
 */
class AddCustomer: public MenuHandler {
public:
	/**
	 * Construtor da classe AddCustomer.
	 * @param pool
	 */
	AddCustomer(Pool & pool);
	/**
	 * Fun��o encarregue de criar a interface necess�ria para que o utilizador crie um cliente.
	 * @return
	 */
	MenuResult handle();
private:
	/**
	 * Refer�ncia � pool, com a inten��o de adicionar um Customer � mesma.
	 */
	Pool & pool;
};

/**
 * Sele��o do Menu referente � remo��o de um cliente � base de dados.
 */
class RemoveCustomer: public MenuHandler {
public:
	/**
	 * Construtor da classe RemoveCustomer.
	 * @param pool
	 */
	RemoveCustomer(Pool & pool);
	/**
	 * Fun��o encarregue de criar a interface necess�ria para que o utilizador elimine um cliente.
	 * @return
	 */
	MenuResult handle();
private:
	/**
	 * Refer�ncia � pool, com a inten��o de retirar um Customer � mesma.
	 */
	Pool & pool;
};

/**
 * Sele��o do Menu referente � adi��o de um professor � base de dados.
 */
class AddTeacher: public MenuHandler {
public:
	/**
	 * Construtor da classe AddTeacher.
	 * @param pool
	 */
	AddTeacher(Pool & pool);
	/**
	 * Fun��o encarregue de criar a interface necess�ria para que o utilizador crie um professor.
	 * @return
	 */
	MenuResult handle();
private:
	/**
	 * Refer�ncia � pool, com a inten��o de adicionar um Teacher � mesma.
	 */
	Pool & pool;
};

/**
 *  Sele��o do Menu referente � remo��o de um professor � base de dados.
 */
class RemoveTeacher: public MenuHandler {
public:
	/**
	 * Construtor da classe RemoveTeacher.
	 * @param pool
	 */
	RemoveTeacher(Pool & pool);
	/**
	 * Fun��o encarregue de criar a interface necess�ria para que o utilizador remova um professor.
	 * @return
	 */
	MenuResult handle();
private:
	/**
	 * Refer�ncia � pool, com a inten��o de remover um Teacher da mesma.
	 */
	Pool & pool;
};

/* ATTEND LESSON */
/**
 * \brief Associa um cliente a uma aula dada.
 *
 * Prioridade daqueles que v�o a uma aula est� subjacente � maneira de como o cliente se inscreve na aula.
 * Uma pessoa que use o modo livre vai frequentar a piscina na hora atual.
 * Uma pessoa que queira frequentar a aula, ter� acesso a uma lista de aulas desse dia para escolher, sendo que marcar� com anteced�ncia, e impedir�
 * aquele que ir� usar o modo livre de usar a piscina, no caso de esta estar cheia.
 */
class AttendLesson: public MenuHandler {
public:
	/**
	 * Construtor da classe AttendLesson
	 * @param pool
	 */
	AttendLesson(Pool & pool);
	/**
	 * Fun��o encarregue de criar a interface necess�ria � associa��o de um Customer a uma Lesson.
	 * @return
	 */
	MenuResult handle();
private:
	/**
	 * Refer�ncia � pool, com a inten��o de modificar o vetor de GivenLessons
	 */
	Pool & pool;
};

/**
 * \brief Semelhante ao Attend Lesson, mas desta vez procura a aula por modalidade.
 * Se n�o encontrar nenhuma aula da modalidade, procura nas outras piscinas (que est�o numa fila de prioridade por dist�ncia) por uma piscina que tenha essa modalidade.
 */
class AttendToSpecificModality: public MenuHandler {
public:
	/**
	 * Construtor da classe AttendToSpecificModality.
	 * @param pool
	 */
	AttendToSpecificModality(Pool & pool);
	/**
	 * Fun��o encarregue de criar a interface necess�ria � associa��o de um Customer a uma Lesson com a modalidade pedida.
	 * @return
	 */
	MenuResult handle();
private:
	/**
	 * Refer�ncia � pool, com a inten��o de modificar o vetor de GivenLessons e ter acesso � fila de prioridade de OtherPools.
	 */
	Pool & pool;
};

/**
 * Adiciona uma aula ao hor�rio.
 */
class AddLesson: public MenuHandler {
public:
	/**
	 * Construtor da classe AddLesson.
	 * @param pool
	 */
	AddLesson(Pool & pool);
	/**
	 * Fun��o encarregue de criar a interface necess�ria � adi��o de uma aula ao hor�rio(com a modalidade pretendida).
	 * @return
	 */
	MenuResult handle();
private:
	/**
	 * Refer�ncia � pool, com a inten��o de modificar o Schedule.
	 */
	Pool & pool;
};

/**
 * Remove uma aula do hor�rio
 */
class RemoveLesson: public MenuHandler {
public:
	/**
	 * Construtor da classe RemoveLesson.
	 * @param pool
	 */
	RemoveLesson(Pool & pool);
	/**
	 * Fun��o encarregue de criar a interface necess�ria � remo��o de uma aula ao hor�rio.
	 * @return
	 */
	MenuResult handle();
private:
	/**
	 * Refer�ncia � pool, com a intan��o de modificar o Schedule.
	 */
	Pool & pool;
};

/**
 * Mostra a ocupa��o atual da piscina.
 */
class CurrentOccupation: public MenuHandler {
public:
	/**
	 * Construtor da classe CurrentOccupation.
	 * @param pool
	 */
	CurrentOccupation(Pool & pool);
	/**
	 * Fun��o encarregue de mostrar a ocupa��o da piscina de um modo user friendly.
	 * @return
	 */
	MenuResult handle();
private:
	/**
	 * Refer�ncia � pool, para acesso � informa��o.
	 */
	Pool & pool;
};

/* CUSTOMERS  ATTENDANCE */
/**
 * Mostra todos os usos de um cliente.
 */
class ViewAttendance: public MenuHandler {
public:
	/**
	 * Construtor da classe ViewAttendance.
	 * @param pool
	 */
	ViewAttendance(Pool& pool);
	/**
	 * Fun��o encarregue de mostrar os usos de um cliente de modo user friendly.
	 * @return
	 */
	MenuResult handle();
private:
	/**
	 *  Refer�ncia � pool, para acesso � informa��o.
	 */
	Pool& pool;
};

/**
 * Cria ficheiros de texto com o recibo de um cliente do m�s atual (at� � data de hoje).
 */
class CustomerMakeCurrentBill: public MenuHandler {
public:
	/**
	 * Construtor da classe CustomerMakeCurrentBill
	 * @param pool
	 */
	CustomerMakeCurrentBill(Pool& pool);
	/**
	 * Fun��o encarregue de pedir o cliente e de criar o ficheiro de texto.
	 * @return
	 */
	MenuResult handle();
private:
	/**
	 * Refer�ncia � pool, para acesso � informa��o.
	 */
	Pool& pool;
};
/**
 * Cria ficheiros de texto com o recibo de um cliente de um m�s � escolha.
 */
class CustomerMakeBill: public MenuHandler {
public:
	/**
	 * Construtor da classe CustomerMakeBill.
	 * @param pool
	 */
	CustomerMakeBill(Pool & pool);
	/**
	 * Fun��o encarregue de pedir o cliente e o m�s, e de criar o ficheiro de texto.
	 * @return
	 */
	MenuResult handle();
private:
	/**
	 * Refer�ncia � pool, para acesso � informa��o.
	 */
	Pool & pool;
};
/**
 * Mostra aulas atribuidas a um professor.
 */
class ViewTeacherSchedule: public MenuHandler {
public:
	/**
	 * Construtor da classe ViewTeacherSchedule.
	 */
	ViewTeacherSchedule(Pool & pool);
	/**
	 * Fun��o encarregue de mostrar as aulas atribuidas a um professor de modo user friendly.
	 * @return
	 */
	MenuResult handle();
private:
	/**
	 * Refer�ncia � pool, para acesso � informa��o.
	 */
	Pool & pool;
};
/**
 * Mostra aulas j� dadas por um professor.
 */
class ViewTeacherGivenLessons: public MenuHandler {
public:
	/**
	 * Construtor da classe ViewTeacherGivenLessons.
	 * @param pool
	 */
	ViewTeacherGivenLessons(Pool & pool);
	/**
	 * Fun��o encarregue de mostrar as aulas j� dadas por um professor de modo user friendly.
	 * @return
	 */
	MenuResult handle();
private:
	/**
	 * Refer�ncia � pool, para acesso � informa��o.
	 */
	Pool & pool;
};

/**
 * Mostra o hor�rio da piscina.
 */
class ViewSchedule: public MenuHandler {
public:
	/**
	 * Construtor da classe ViewSchedule.
	 * @param pool
	 */
	ViewSchedule(Pool & pool);
	/**
	 * Fun��o encarregue de mostrar o hor�rio da piscina de modo user friendly.
	 * @return
	 */
	MenuResult handle();
private:
	/**
	 * Refer�ncia � pool, para acesso � informa��o.
	 */
	Pool & pool;
};

/**
 * Mostra todos os professores da piscina.
 */
class ViewTeachers: public MenuHandler {
public:
	/**
	 * Construtor da classe ViewTeachers.
	 * @param pool
	 * @param orderBy
	 */
	ViewTeachers(Pool & pool, OrderBy orderBy);
	/**
	 * Fun��o encarregue de mostrar os professores (por ordem segundo OrderBy) de modo user friendly.
	 * @return
	 */
	MenuResult handle();
private:
	/**
	 * Refer�ncia � pool, para acesso � informa��o.
	 */
	Pool & pool;
	/**
	 * Enum OrderBy, serve para saber se ordenamos os professores por nome, aulas dadas, n�mero de aulas atribuidas ou por id (este membro � decidido nos menus, onde existem v�rias op��es para escolhe-lo).
	 */
	OrderBy orderBy;
};

/**
 * Mostra todos os clientes da piscina.
 */
class ViewCustomers: public MenuHandler {
public:
	/**
	 * Construtor da classe ViewCustomers.
	 * @param pool
	 * @param orderBy
	 */
	ViewCustomers(Pool & pool, OrderBy orderBy);
	/**
	 * Fun��o encarregue de mostrar os clientes (por ordem segundo OrderBy) de modo user friendly.
	 * @return
	 */
	MenuResult handle();
private:
	/**
	 * Refer�ncia � pool, para acesso � informa��o.
	 */
	Pool & pool;
	/**
	 * Enum OrderBy, serve para saber se ordenamos os clientes por nome, por ID ou por n�mero de aulas assistidas(este membro � decidido nos menus, onde existem v�rias op��es para escolhe-lo).
	 */
	OrderBy orderBy;
};

/**
 * Adiciona um uso livre a um cliente.
 */
class FreeSwimming: public MenuHandler {
public:
	/**
	 * Construtor da classe FreeSwimming.
	 * @param pool
	 */
	FreeSwimming(Pool & pool);
	/**
	 * Fun��o encarregue de pedir o cliente, verificar se a piscina est� cheia, e adicionar um uso ao cliente.
	 * @return
	 */
	MenuResult handle();
private:
	/**
	 * Refer�ncia � pool, para acesso � informa��o e modifica��o do vetor de clientes.
	 */
	Pool & pool;
};

/**
 * Mostra a informa��o de um cliente.
 */
class ViewCustomersInformation: public MenuHandler {
public:
	/**
	 * Construtor da classe ViewCustomersInformation.
	 * @param pool
	 */
	ViewCustomersInformation(Pool & pool);
	/**
	 * Fun��o encarregue de pedir o cliente e mostrar a sua informa��o de forma user friendly.
	 * @return
	 */
	MenuResult handle();
private:
	/**
	 * Refer�ncia � pool, para acesso � informa��o.
	 */
	Pool & pool;
};

/**
 * Mostra todos os usos de piscina livre de um cliente.
 */
class ViewCustomerUses: public MenuHandler {
public:
	/**
	 * Construtor da classe ViewCustomerUses.
	 * @param pool
	 */
	ViewCustomerUses(Pool & pool);
	/**
	 * Fun��o encarregue de mostrar os usos de um cliente de forma user friendly.
	 * @return
	 */
	MenuResult handle();
private:
	/**
	 * Refer�ncia � pool, para acesso � informa��o.
	 */
	Pool & pool;
};

/**
 * Mostra informa��o relativa a um professor.
 */
class ViewTeacherInformation: public MenuHandler {
public:
	/**
	 * Construtor da classe ViewTeacherInformation.
	 * @param pool
	 */
	ViewTeacherInformation(Pool & pool);
	/**
	 * Fun��o encarregue de mostrar a informa��o do professor de forma user friendly.
	 * @return
	 */
	MenuResult handle();
private:
	/**
	 * Refer�ncia � pool, para acesso � informa��o.
	 */
	Pool & pool;
};

/**
 * Trata da venda de produtos aos clientes.
 */
//TODO: guardar as compras ja feitas num ficheiro e num vetor
class ShopSellItems: public MenuHandler {
public:
	/**
	 * Construtor da classe ShopSellItems.
	 */
	ShopSellItems(Pool & pool);
	/**
	 * Fun��o encarregue de verificar stock e vender produtos aos clientes.
	 * @return
	 */
	MenuResult handle();
private:
	/**
	 * Refer�ncia � pool, para acesso � informa��o e modifica��o da Shop.
	 */
	Pool & pool;
};

/**
 * Trata da compra de produtos ao fornecedor.
 */
class ShopBuyItems: public MenuHandler {
public:
	/**
	 * Construtor da classe ShopBuyItems.
	 * @param pool
	 */
	ShopBuyItems(Pool & pool);
	/**
	 *  Fun��o encarregue de aumentar o stock da loja.
	 * @return
	 */
	MenuResult handle();
private:
	/**
	 * Refer�ncia � pool, para acesso � informa��o e modifica��o da Shop.
	 */
	Pool & pool;
};

/**
 * Mostra os itens da loja, bem como o seu stock atual.
 */
class ViewShopInfo: public MenuHandler {
public:
	/**
	 * Construtor da classe ViewShopInfo.
	 * @param pool
	 */
	ViewShopInfo(Pool & pool);
	/**
	 * Fun��o encarregue de mostrar a informa��o da loja de modo user friendly.
	 * @return
	 */
	MenuResult handle();
private:
	/**
	 * Refer�ncia � pool para acesso � informa��o.
	 */
	Pool & pool;
};

/*
 * ver informacoes e alterar iformacoes das piscinas proximas da nossa piscina
 * */

/**
 * Mostra as piscinas nas proximidades, bem como as modalidades que apresenta.
 */
class ViewOtherPools: public MenuHandler {
public:
	/**
	 * Construtor da classe ViewOtherPools.
	 * @param pool
	 */
	ViewOtherPools(Pool & pool);
	/**
	 * Fun��o encarregue de mostrar as outras piscinas, por ordem de proximidade, e as suas modalidades, de modo user friendly.
	 * @return
	 */
	MenuResult handle();
private:
	/**
	 * Refer�ncia � pool para acesso � informa��o.
	 */
	Pool & pool;
};

/**
 * Adiciona outra piscina � fila de prioridade
 */
class AddOtherPool: public MenuHandler {
public:
	/**
	 * Construtor da classe AddOtherPool.
	 * @param pool
	 */
	AddOtherPool(Pool & pool);
	/**
	 * Fun��o encarregue de pedir informa��es da piscina e adicion�-la.
	 * @return
	 */
	MenuResult handle();
private:
	/**
	 * Refer�ncia � pool para modifica��o da fila de prioridade de OtherPool.
	 */
	Pool & pool;
};

/**
 * Adicionar uma modalidade a uma piscina.
 */
class AddModalityToPool: public MenuHandler {
public:
	/**
	 * Construtor da classe AddModalityToPool.
	 * @param pool
	 */
	AddModalityToPool(Pool & pool);
	/**
	 * Fun��o encarregue de adicionar uma modalidade a uma OtherPool.
	 * @return
	 */
	MenuResult handle();
private:
	/**
	 * Refer�ncia � pool para modifica��o da fila de prioridade de OtherPool.
	 */
	Pool & pool;
};

/*
 * Promotional Campaign Manage
 */
/**
 * Mostra a campanha atual.
 */
class ViewCurrentCampaign: public MenuHandler {
public:
	/**
	 * Construtor da classe ViewCurrentCampaign.
	 * @param pool
	 */
	ViewCurrentCampaign(Pool & pool);
	/**
	 * Fun��o encarregue de mostrar, de forma user friendly, a campanha promocional ativa no momento (se houver).
	 * @return
	 */
	MenuResult handle();
private:
	/**
	 * Refer�ncia � pool para acesso � informa��o.
	 */
	Pool & pool;
};

/**
 * Cria uma campanha promocional.
 */
class AddCampaign: public MenuHandler {
public:
	/**
	 * Construtor da classe AddCampaign.
	 * @param pool
	 */
	AddCampaign(Pool & pool);
	/**
	 * Fun��o encarregue de verificar se a campanha promocional criada interseta outra j� existente, e adicion�-la.
	 * @return
	 */
	MenuResult handle();
private:
	/**
	 * Refer�ncia � pool para acesso � informa��o e modifica��o do vetor de campanhas pormocionais.
	 */
	Pool & pool;
};

/**
 * Atualiza a tabela de dispers�o de clientes inativos.
 */
class UpdateCustomersInfo: public MenuHandler {
public:
	/**
	 * Construtor da classe UpdateCustomersInfo.
	 * @param pool
	 */
	UpdateCustomersInfo(Pool & pool);
	/**
	 * Fun��o encarregue de criar a interface necess�ria � atualiza��o dos clientes.
	 * @return
	 */
	MenuResult handle();
private:
	/**
	 * Refer�ncia � pool para acesso � informa��o e modifica��o da tabela de dispers�o.
	 */
	Pool & pool;
};
#endif /* SRC_POOLMENU_H_ */


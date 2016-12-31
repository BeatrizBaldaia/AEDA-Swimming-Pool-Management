#ifndef SRC_POOLMENU_H_
#define SRC_POOLMENU_H_

#include "Menu.h"

enum OrderBy {
	ID, NAME, NUMUSES, GIVENLESSONS, ASSLESSONS
};

class Pool;

/* POOL MENU */
/**
 * cria menus (é derivada da class Menu).
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
	 * referência à pool (onde é guardada toda a informação) para depois ser passada para as outras classes.
	 */
	Pool & pool;
};

/**
 * Seleção do Menu referente à adição de um cliente à base de dados.
 */
class AddCustomer: public MenuHandler {
public:
	/**
	 * Construtor da classe AddCustomer.
	 * @param pool
	 */
	AddCustomer(Pool & pool);
	/**
	 * Função encarregue de criar a interface necessária para que o utilizador crie um cliente.
	 * @return
	 */
	MenuResult handle();
private:
	/**
	 * Referência à pool, com a intenção de adicionar um Customer à mesma.
	 */
	Pool & pool;
};

/**
 * Seleção do Menu referente à remoção de um cliente à base de dados.
 */
class RemoveCustomer: public MenuHandler {
public:
	/**
	 * Construtor da classe RemoveCustomer.
	 * @param pool
	 */
	RemoveCustomer(Pool & pool);
	/**
	 * Função encarregue de criar a interface necessária para que o utilizador elimine um cliente.
	 * @return
	 */
	MenuResult handle();
private:
	/**
	 * Referência à pool, com a intenção de retirar um Customer à mesma.
	 */
	Pool & pool;
};

/**
 * Seleção do Menu referente à adição de um professor à base de dados.
 */
class AddTeacher: public MenuHandler {
public:
	/**
	 * Construtor da classe AddTeacher.
	 * @param pool
	 */
	AddTeacher(Pool & pool);
	/**
	 * Função encarregue de criar a interface necessária para que o utilizador crie um professor.
	 * @return
	 */
	MenuResult handle();
private:
	/**
	 * Referência à pool, com a intenção de adicionar um Teacher à mesma.
	 */
	Pool & pool;
};

/**
 *  Seleção do Menu referente à remoção de um professor à base de dados.
 */
class RemoveTeacher: public MenuHandler {
public:
	/**
	 * Construtor da classe RemoveTeacher.
	 * @param pool
	 */
	RemoveTeacher(Pool & pool);
	/**
	 * Função encarregue de criar a interface necessária para que o utilizador remova um professor.
	 * @return
	 */
	MenuResult handle();
private:
	/**
	 * Referência à pool, com a intenção de remover um Teacher da mesma.
	 */
	Pool & pool;
};

/* ATTEND LESSON */
/**
 * \brief Associa um cliente a uma aula dada.
 *
 * Prioridade daqueles que vão a uma aula está subjacente à maneira de como o cliente se inscreve na aula.
 * Uma pessoa que use o modo livre vai frequentar a piscina na hora atual.
 * Uma pessoa que queira frequentar a aula, terá acesso a uma lista de aulas desse dia para escolher, sendo que marcará com antecedência, e impedirá
 * aquele que irá usar o modo livre de usar a piscina, no caso de esta estar cheia.
 */
class AttendLesson: public MenuHandler {
public:
	/**
	 * Construtor da classe AttendLesson
	 * @param pool
	 */
	AttendLesson(Pool & pool);
	/**
	 * Função encarregue de criar a interface necessária à associação de um Customer a uma Lesson.
	 * @return
	 */
	MenuResult handle();
private:
	/**
	 * Referência à pool, com a intenção de modificar o vetor de GivenLessons
	 */
	Pool & pool;
};

/**
 * \brief Semelhante ao Attend Lesson, mas desta vez procura a aula por modalidade.
 * Se não encontrar nenhuma aula da modalidade, procura nas outras piscinas (que estão numa fila de prioridade por distância) por uma piscina que tenha essa modalidade.
 */
class AttendToSpecificModality: public MenuHandler {
public:
	/**
	 * Construtor da classe AttendToSpecificModality.
	 * @param pool
	 */
	AttendToSpecificModality(Pool & pool);
	/**
	 * Função encarregue de criar a interface necessária à associação de um Customer a uma Lesson com a modalidade pedida.
	 * @return
	 */
	MenuResult handle();
private:
	/**
	 * Referência à pool, com a intenção de modificar o vetor de GivenLessons e ter acesso à fila de prioridade de OtherPools.
	 */
	Pool & pool;
};

/**
 * Adiciona uma aula ao horário.
 */
class AddLesson: public MenuHandler {
public:
	/**
	 * Construtor da classe AddLesson.
	 * @param pool
	 */
	AddLesson(Pool & pool);
	/**
	 * Função encarregue de criar a interface necessária à adição de uma aula ao horário(com a modalidade pretendida).
	 * @return
	 */
	MenuResult handle();
private:
	/**
	 * Referência à pool, com a intenção de modificar o Schedule.
	 */
	Pool & pool;
};

/**
 * Remove uma aula do horário
 */
class RemoveLesson: public MenuHandler {
public:
	/**
	 * Construtor da classe RemoveLesson.
	 * @param pool
	 */
	RemoveLesson(Pool & pool);
	/**
	 * Função encarregue de criar a interface necessária à remoção de uma aula ao horário.
	 * @return
	 */
	MenuResult handle();
private:
	/**
	 * Referência à pool, com a intanção de modificar o Schedule.
	 */
	Pool & pool;
};

/**
 * Mostra a ocupação atual da piscina.
 */
class CurrentOccupation: public MenuHandler {
public:
	/**
	 * Construtor da classe CurrentOccupation.
	 * @param pool
	 */
	CurrentOccupation(Pool & pool);
	/**
	 * Função encarregue de mostrar a ocupação da piscina de um modo user friendly.
	 * @return
	 */
	MenuResult handle();
private:
	/**
	 * Referência à pool, para acesso à informação.
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
	 * Função encarregue de mostrar os usos de um cliente de modo user friendly.
	 * @return
	 */
	MenuResult handle();
private:
	/**
	 *  Referência à pool, para acesso à informação.
	 */
	Pool& pool;
};

/**
 * Cria ficheiros de texto com o recibo de um cliente do mês atual (até à data de hoje).
 */
class CustomerMakeCurrentBill: public MenuHandler {
public:
	/**
	 * Construtor da classe CustomerMakeCurrentBill
	 * @param pool
	 */
	CustomerMakeCurrentBill(Pool& pool);
	/**
	 * Função encarregue de pedir o cliente e de criar o ficheiro de texto.
	 * @return
	 */
	MenuResult handle();
private:
	/**
	 * Referência à pool, para acesso à informação.
	 */
	Pool& pool;
};
/**
 * Cria ficheiros de texto com o recibo de um cliente de um mês à escolha.
 */
class CustomerMakeBill: public MenuHandler {
public:
	/**
	 * Construtor da classe CustomerMakeBill.
	 * @param pool
	 */
	CustomerMakeBill(Pool & pool);
	/**
	 * Função encarregue de pedir o cliente e o mês, e de criar o ficheiro de texto.
	 * @return
	 */
	MenuResult handle();
private:
	/**
	 * Referência à pool, para acesso à informação.
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
	 * Função encarregue de mostrar as aulas atribuidas a um professor de modo user friendly.
	 * @return
	 */
	MenuResult handle();
private:
	/**
	 * Referência à pool, para acesso à informação.
	 */
	Pool & pool;
};
/**
 * Mostra aulas já dadas por um professor.
 */
class ViewTeacherGivenLessons: public MenuHandler {
public:
	/**
	 * Construtor da classe ViewTeacherGivenLessons.
	 * @param pool
	 */
	ViewTeacherGivenLessons(Pool & pool);
	/**
	 * Função encarregue de mostrar as aulas já dadas por um professor de modo user friendly.
	 * @return
	 */
	MenuResult handle();
private:
	/**
	 * Referência à pool, para acesso à informação.
	 */
	Pool & pool;
};

/**
 * Mostra o horário da piscina.
 */
class ViewSchedule: public MenuHandler {
public:
	/**
	 * Construtor da classe ViewSchedule.
	 * @param pool
	 */
	ViewSchedule(Pool & pool);
	/**
	 * Função encarregue de mostrar o horário da piscina de modo user friendly.
	 * @return
	 */
	MenuResult handle();
private:
	/**
	 * Referência à pool, para acesso à informação.
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
	 * Função encarregue de mostrar os professores (por ordem segundo OrderBy) de modo user friendly.
	 * @return
	 */
	MenuResult handle();
private:
	/**
	 * Referência à pool, para acesso à informação.
	 */
	Pool & pool;
	/**
	 * Enum OrderBy, serve para saber se ordenamos os professores por nome, aulas dadas, número de aulas atribuidas ou por id (este membro é decidido nos menus, onde existem vérias opções para escolhe-lo).
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
	 * Função encarregue de mostrar os clientes (por ordem segundo OrderBy) de modo user friendly.
	 * @return
	 */
	MenuResult handle();
private:
	/**
	 * Referência à pool, para acesso à informação.
	 */
	Pool & pool;
	/**
	 * Enum OrderBy, serve para saber se ordenamos os clientes por nome, por ID ou por número de aulas assistidas(este membro é decidido nos menus, onde existem vérias opções para escolhe-lo).
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
	 * Função encarregue de pedir o cliente, verificar se a piscina está cheia, e adicionar um uso ao cliente.
	 * @return
	 */
	MenuResult handle();
private:
	/**
	 * Referência à pool, para acesso à informação e modificação do vetor de clientes.
	 */
	Pool & pool;
};

/**
 * Mostra a informação de um cliente.
 */
class ViewCustomersInformation: public MenuHandler {
public:
	/**
	 * Construtor da classe ViewCustomersInformation.
	 * @param pool
	 */
	ViewCustomersInformation(Pool & pool);
	/**
	 * Função encarregue de pedir o cliente e mostrar a sua informação de forma user friendly.
	 * @return
	 */
	MenuResult handle();
private:
	/**
	 * Referência à pool, para acesso à informação.
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
	 * Função encarregue de mostrar os usos de um cliente de forma user friendly.
	 * @return
	 */
	MenuResult handle();
private:
	/**
	 * Referência à pool, para acesso à informação.
	 */
	Pool & pool;
};

/**
 * Mostra informação relativa a um professor.
 */
class ViewTeacherInformation: public MenuHandler {
public:
	/**
	 * Construtor da classe ViewTeacherInformation.
	 * @param pool
	 */
	ViewTeacherInformation(Pool & pool);
	/**
	 * Função encarregue de mostrar a informação do professor de forma user friendly.
	 * @return
	 */
	MenuResult handle();
private:
	/**
	 * Referência à pool, para acesso à informação.
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
	 * Função encarregue de verificar stock e vender produtos aos clientes.
	 * @return
	 */
	MenuResult handle();
private:
	/**
	 * Referência à pool, para acesso à informação e modificação da Shop.
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
	 *  Função encarregue de aumentar o stock da loja.
	 * @return
	 */
	MenuResult handle();
private:
	/**
	 * Referência à pool, para acesso à informação e modificação da Shop.
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
	 * Função encarregue de mostrar a informação da loja de modo user friendly.
	 * @return
	 */
	MenuResult handle();
private:
	/**
	 * Referência à pool para acesso à informação.
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
	 * Função encarregue de mostrar as outras piscinas, por ordem de proximidade, e as suas modalidades, de modo user friendly.
	 * @return
	 */
	MenuResult handle();
private:
	/**
	 * Referência à pool para acesso à informação.
	 */
	Pool & pool;
};

/**
 * Adiciona outra piscina à fila de prioridade
 */
class AddOtherPool: public MenuHandler {
public:
	/**
	 * Construtor da classe AddOtherPool.
	 * @param pool
	 */
	AddOtherPool(Pool & pool);
	/**
	 * Função encarregue de pedir informações da piscina e adicioná-la.
	 * @return
	 */
	MenuResult handle();
private:
	/**
	 * Referência à pool para modificação da fila de prioridade de OtherPool.
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
	 * Função encarregue de adicionar uma modalidade a uma OtherPool.
	 * @return
	 */
	MenuResult handle();
private:
	/**
	 * Referência à pool para modificação da fila de prioridade de OtherPool.
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
	 * Função encarregue de mostrar, de forma user friendly, a campanha promocional ativa no momento (se houver).
	 * @return
	 */
	MenuResult handle();
private:
	/**
	 * Referência à pool para acesso à informação.
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
	 * Função encarregue de verificar se a campanha promocional criada interseta outra já existente, e adicioná-la.
	 * @return
	 */
	MenuResult handle();
private:
	/**
	 * Referência à pool para acesso à informação e modificação do vetor de campanhas pormocionais.
	 */
	Pool & pool;
};

/**
 * Atualiza a tabela de dispersão de clientes inativos.
 */
class UpdateCustomersInfo: public MenuHandler {
public:
	/**
	 * Construtor da classe UpdateCustomersInfo.
	 * @param pool
	 */
	UpdateCustomersInfo(Pool & pool);
	/**
	 * Função encarregue de criar a interface necessária à atualização dos clientes.
	 * @return
	 */
	MenuResult handle();
private:
	/**
	 * Referência à pool para acesso à informação e modificação da tabela de dispersão.
	 */
	Pool & pool;
};
#endif /* SRC_POOLMENU_H_ */


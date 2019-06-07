#include "./../Headers/Interface.h"

Interface::Interface(){
    // Inicializa tela
    initscr();
    // Posicoes do cursor
    x = y = 5;
    
    int c = 0;
    int b;

    // Cria menu inicial
    menuInicial();
    // Loop infinito ate que o cliente saia da aplicacao
    while(c != 113){ // 'q' quit
        c = getch();
        if(c == 113){break;}

        b = getch(); // VARIAVEL AUXILIAR PARA ENTRADA
        if(c != 113){
            try{
                switchMenu(c);
            }
            catch (Excecao& e){
                /* string excecao = e.getExcecao();
                char* ptr_char_excecao = excecao.c_str();
                print(ptr_char_excecao); */
            }
        }
    }
}

Interface::~Interface(){
    endwin();
}

void Interface::print(const char* text, bool breakLine = true){
    mvprintw(y, x, text);
    if(breakLine){
        y++;
    }
}

void Interface::setMenu(){
    y = x = 5;
    clear();
}

void Interface::getString()
{
    nocbreak();
    echo();

    input.clear();

    int ch = getch();

    while ( ch != '\n' )
    {
        input.push_back( ch );
        ch = getch();
    }
}

void Interface::switchMenu(int option){

    switch (option)
    {
        case 97:
            menuCadastroCliente();
            break;
        case 98:
            menuCadastroPlano();
            break;
        case 99:
            menuCadastroCelular();
            break;
        case 100:
            menuAdicionaCreditos();
            break;
        case 101:
            menuRegistraLigacaoS();
            break;
        case 102:
            menuRegistraLigacaoD();
            break;
        case 103:
            listaDadosPacote();
            break;
        case 104:
            listaValorConta();
            break;
        case 105:
            listaCreditos();
            break;
        case 106:
            listaExtratoS();
            break;
        case 107:
            listaExtratoD();
            break;
        case 108:
            listaClientes();
            break;
        case 109:
            listaPlanos();
            break;
        case 110:
            listaCelulares();
            break;
        case 111:
            informaVencimentos();
            break;
        case 112:
            informaLimiteFranquia();
            break;
        default:
            break;
    }
}

void Interface::menuInicial(){

    setMenu();

    print("///// OPERADORA TELEFONICA CONAUT /////");
    print("a. Cadastro de Clientes");
    print("b. Cadastro de Planos");
    print("c. Cadastro de Celulares");
    print("d. Adicionar Creditos");
    print("e. Registro de Ligacao Simples");
    print("f. Registro de Ligacao de Dados");
    print("g. Informacao de Pacote de Dados");
    print("h. Valor de Contas");
    print("i. Saldo de Creditos");
    print("j. Extrato de Ligacoes Simples");
    print("k. Extrato de Ligacoes de Dados");
    print("l. Lista de Clientes");
    print("m. Lista de Planos");
    print("n. Lista de Celulares");
    print("o. Informe de Vencimentos");
    print("p. Limite de Franquia");
    print("Pressione q para sair");
    print("Escolha uma opcao: ");

    refresh();
}

void Interface::menuCadastroCliente(){

    string nome, CPF, endereco;

    setMenu();

    print("///// MENU DE CADASTRO DE CLIENTES /////");
    
    print("ENTRE COM OS DADOS DO CLIENTE: ");
    print("NOME DO CLIENTE: ");
    getString();
    nome = input;
    print("ENDERECO: ");
    getString();
    CPF = input;
    print("CPF/CNPJ: ");
    getString();
    endereco = input;
    
    refresh();

    // CRIA CLIENTE
    Cliente c(CPF, nome, endereco);

    menuInicial();
}

void Interface::menuCadastroPlano(){

    setMenu();

    string nome;
    int vlrMinuto, franquia, veloc, velocAlem;

    print("///// MENU DE CADASTRO DE PLANOS /////");
    print("NOME DO PLANO: ");
    getString();
    nome = input;
    print("VALOR DO MINUTO: ");
    getString();
    vlrMinuto = stoi(input);
    print("VELOCIDADE DO PACOTE DE DADOS: ");
    getString();
    veloc = stoi(input);
    print("FRANQUIA: ");
    getString();
    franquia = stoi(input);
    print("VELOCIDADE ALEM DA FRANQUIA: ");
    getString();
    velocAlem = stoi(input);
    print("TIPO DO PLANO: ");
    getString();
    if(input == "PosPago"){
        print("DATA DE VENCIMENTO: ");
        getString();
        input;
        // TO-DO: FUNC CONVERTER STRING PARA DATA
    }else if(input == "PrePago"){
        print("VALOR CREDITO: ");
        getString();
        // TO-DO: RECEBER A DATA ATUAL E ADICIONAR 180dias.
        // PrePago sub_p();
    }else{ // Pós-Pago
        throw Excecao();
        // TO-DO: ESPECIFICAR EXCECAO
        // A FUNCAO TRY: SERA CHAMADA NA CONSTRUCAO DA CLASSE
        // DENTRO DO WHILE
        // PosPago sub_p();
    }
    

    // CRIA OBJETO PLANO
    /*
    Plano* p = &sub_p;
    planos.insert(make_pair(nome, p));
    */

    refresh();
    menuInicial();
}

void Interface::menuCadastroCelular(){

    Cliente* ptr_cliente;
    string nome_plano;
    double numero, n_cliente, vlr_minuto, franquia, velocAlem, veloc, credito;
    // TO-DO: TRY COM STOI

    setMenu();

    print("///// MENU DE CADASTRO DE CELULARES /////");
    print("NUMERO DO CELULAR");
    getString();
    numero = stoi(input);
    print("NUMERO DO CLIENTE(A PARTIR DE 1): ");
    getString();
    n_cliente = stoi(input);
    if(n_cliente <= clientes.size()){
        n_cliente--;
        ptr_cliente = &clientes[n_cliente];
    }else{
        throw Excecao();
    }
    // TO-DO: VERIFICAR O NUMERO DO CLIENTE E JOGAR THROW
    print("NOME DO PLANO: ");
    getString();
    nome_plano = input;
    if(planos.find(nome_plano) == planos.end()){
        throw Excecao();
    }else{
        Plano* p = planos.find(nome_plano)->second;
        PosPago* ptr_posPago = dynamic_cast<PosPago*>(p);

        vlr_minuto = p->getValorMinuto();
        franquia = p->getFranquia();
        velocAlem = p->getVelocAlem();
        veloc = p->getVelocidade();
        if(ptr_posPago != nullptr){ // Pós-Pago
            print("DATA DE VENCIMENTO: ");
            getString();
            // TO-DO: PROCESSAR DATA
            // d = data;
            //ptr_cliente->addCelular(nome_plano, vlr_minuto, franquia, velocAlem, veloc, data_vencimento);

        }else{ // Pre-Pago
            print("CREDITO INICIAL: ");
            getString();
            credito = stoi(input);
            // CRIAR DATA COM DATA ATUAL E ADICIONAR 180 dias e colocar aqui.
            // validade = data;
            //ptr_cliente->addCelular(nome_plano, vlr_minuto, franquia, velocAlem, veloc, data_atual, credito);
        }
    }

    refresh();
    menuInicial();
}

void Interface::menuAdicionaCreditos(){

    setMenu();

    print("///// MENU DE CREDITOS /////");
    print("NUMERO DO CELULAR: ");
    getString();
    print("VALOR DE CREDITOS: ");
    getString();

    // TO-DO: Atulizar data para data atual + 180 dias.
    
    refresh();
    menuInicial();
}

void Interface::menuRegistraLigacaoS(){

    setMenu();
    print("///// MENU DE REGISTRO DE LIGACOES SIMPLES /////");
    print("CELULAR: ");
    getString();
    print("DATA: ");
    getString();
    print("DURACAO(MIN): ");
    getString();
    print("# TELEFONE: ");
    getString();

    refresh();
    menuInicial();
}

void Interface::menuRegistraLigacaoD(){

    setMenu();
    print("///// MENU DE REGISTRO DE LIGACOES DE DADOS /////");
    print("CELULAR: ");
    getString();
    print("DATA: ");
    getString();
    print("DURACAO: ");
    getString();
    print("TIPO: ");
    getString();

    refresh();
    menuInicial();
}

void Interface::listaDadosPacote(){

    setMenu();
    print("///// CONSULTA DE DADOS DO PACOTE /////");
    print("CELULAR: ");
    getString();

    refresh();
    menuInicial();

    // TO-DO: TEM QUE RESOLVER O CELULAR --> CLIENTE.
    // CELULAR
    // RETORNA SALDO DADOS
    // RETORNA VELOCIDADE ATUAL (DOWN E UP)
}

void Interface::listaValorConta(){

    setMenu();
    print("///// CONSULTA DE CONTAS /////");
    print("CELULAR : ");
    getString();

    refresh();
    menuInicial();

    // RECEBE CELULAR
    // VALOR TOTAL DAS LIGACOES APOS O DIA DE VENCIMENTO MES ANTERIOR
    // DIA DE VENCIMENTO 
}

void Interface::listaCreditos(){

    setMenu();
    print("///// CONSULTA DE CREDITOS /////");
    print("CELULAR : ");
    getString();

    refresh();
    menuInicial();

    // RECEBE CELULAR
    // LISTA OS CREDITOS 
    // DATA DE VALIDADE DOS CREDITOS
}

void Interface::listaExtratoS(){

    setMenu();
    print("///// CONSULTA DE EXTRATO SIMPLES /////");
    print("CELULAR: ");
    getString();
    print("DATA INICIAL: ");
    getString();

    refresh();
    menuInicial();
    // RECEBE CELULAR
    // RECEBE DATA
    // IMPRIME TODAS AS LIGACOES A PARTIR DA DATA
    // DURACAO
    // VALOR
    // DATA
}

void Interface::listaExtratoD(){

    setMenu();
    print("///// CONSULTA DE EXTRADO DE DADOS /////");
    print("CELULAR: ");
    getString();
    print("DATA INICIAL: ");
    getString();

    refresh();
    menuInicial();
    // RECEBE CELULAR E DATA
    // CONSUMO DE DADOS A PARTIR DA DATA
    // IMPRIMIR DATA, DURACAO, TIPO, E QUANTIDADE CONSUMIDA.
}

void Interface::listaClientes(){
    // LISTA CLIENTES E INFORMACOES
}

void Interface::listaPlanos(){
    // LISTA PLANOS E INFORMACOEs
}

void Interface::listaCelulares(){
    // LISTA CELULARES E INFORMACOES
}

void Interface::informaVencimentos(){
    // SEMPRE QUE UMA FATURA OU CREDITO VENCER
    // INFORMAR AO USUARIO OS DADOS DO CLIENTE E CELULAR
}

void Interface::informaLimiteFranquia(){
    // QUANDO O CONSUMO DE DADOS ALCANCAR O VALOR
    // DA FRANQUIA, INFORMAR OS DADOS DO CLIENTE E CELULAR
}

// TO-DO: HASH TABLE(MAP) CELULAR(INT) --> CLIENTE(INT).
// TO-DO: HASH TABLE NOME PLANO(STRING) --> pair(PLANO(INT), tipo de plano(INT)).
// TO-DO: Exceções: Plano nao existente. Celular não existente. Cliente não existente.
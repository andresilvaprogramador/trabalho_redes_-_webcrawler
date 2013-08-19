#include "http.h"

int main(int argc , char *argv[]) {
	string url;
	int depth;
	string ca;
	switch(argc) {
	case 3:
		//http::certificatePath = "/usr/lib/ssl/certs";
		break;
	case 4:
		ca = argv[3];
		size_t pos;
		http::certificateFile.clear();
		http::certificatePath.clear();
		if ((pos = ca.find("--CAfile=")) != std::string::npos) {
			http::certificateFile = ca.substr(pos+9);
		} else if ((pos = ca.find("--CApath=")) != std::string::npos) {
			http::certificatePath = ca.substr(pos+9);
		}
		break;
	default:
		std::cerr << "parametros invalidos" << std::endl;
		break;
	}
	// Inserindo http, caso seja informada uma url sem http
	boost::regex teste("http|https");
	if(!(boost::regex_search(argv[1], teste))){
		url += "http://";
	}

	url += argv[1];
	if (http::certificateFile.empty() && http::certificatePath.empty())
		std::cerr << "Nenhum certificado local carregado" << std::endl;

	std::cerr << "URL Inicial: " << url << std::endl;
	depth = std::atoi (argv[2]);

	http::Recursive(url,depth);

	std::cout << "Lista URL visitadas:" << std::endl;
	for (unsigned int i = 0; i < http::urlVisited.size();i++) {
		UrlNodo * nodo = http::urlVisited[i];
		std::cout << nodo->url << std::endl ;
		if (nodo->useSsl) {
			std::cout << "		CN: [ " << nodo->CN << " ]" << (!nodo->certificateValidity ? " Certificado não confiável" : "") << std::endl;
			std::cout << "		O/OU: [ " << nodo->O << " ]" << (nodo->autoassinado ? " AUTOASSINADO" : "") << std::endl;
		}
	}

	/**/

	return 0;
}

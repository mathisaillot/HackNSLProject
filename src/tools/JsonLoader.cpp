#include "JsonLoader.hpp"

/*****************************************
 *              constr/destr             *
 *****************************************/
// constr
JsonLoader::JsonLoader(const std::string & destfile) {
    // on transforme notre fichier json en string
    std::string json_str = OutStr::fileToStringOneLine(destfile);
    // 
    Json::CharReaderBuilder builder;
    Json::CharReader * reader = builder.newCharReader(); 
    std::string errors;
    const char * txt = json_str.c_str();
    bool parsingSuccessfull = reader->parse(
        txt,
        txt + json_str.size(),
        &m_data,
        &errors
    );
    delete reader;
    if(!parsingSuccessfull)
        std::cerr << txt    << std::endl << errors << std::endl;
}
// destr
/*virtual*/JsonLoader::~JsonLoader() {}

#include "stopwords.hh"



// Lista de stopwords en catalán
const unordered_set<string> stopwords_ca = {
    "a","abans","ací","ah","així","això","al","aleshores","algun","alguna","algunes","alguns","alhora",
    "allà","allí","allò","als","altra","altre","altres","amb","ambdues","ambdós","anar","ans","apa",
    "aquell","aquella","aquelles","aquells","aquest","aquesta","aquestes","aquests","aquí","baix",
    "bastant","bé","cada","cadascuna","cadascunes","cadascuns","cadascú","com","consegueixo","conseguim",
    "conseguir","consigueix","consigueixen","consigueixes","contra","d'un","d'una","d'unes","d'uns","dalt",
    "de","del","dels","des","des de","després","dins","dintre","donat","doncs","durant","e","eh","el",
    "elles","ells","els","em","en","encara","ens","entre","era","erem","eren","eres","es","esta","estan",
    "estat","estava","estaven","estem","esteu","estic","està","estàvem","estàveu","et","etc","ets","fa",
    "faig","fan","fas","fem","fer","feu","fi","fins","fora","gairebé","ha","han","has","haver","havia","he",
    "hem","heu","hi","ho","i","igual","iguals","inclòs","ja","jo","l'hi","la","les","li","li'n","llarg",
    "llavors","m'he","ma","mal","malgrat","mateix","mateixa","mateixes","mateixos","me","mentre","meu",
    "meus","meva","meves","mode","molt","molta","moltes","molts","mon","mons","més","n'he","n'hi","ne",
    "ni","no","nogensmenys","només","nosaltres","nostra","nostre","nostres","o","oh","oi","on","pas",
    "pel","pels","per","per que","perquè","però","poc","poca","pocs","podem","poden","poder","podeu",
    "poques","potser","primer","propi","puc","qual","quals","quan","quant","que","quelcom","qui","quin",
    "quina","quines","quins","què","s'ha","s'han","sa","sabem","saben","saber","sabeu","sap","saps",
    "semblant","semblants","sense","ser","ses","seu","seus","seva","seves","si","sobre","sobretot",
    "soc","solament","sols","som","son","sons","sota","sou","sóc","són","t'ha","t'han","t'he","ta",
    "tal","també","tampoc","tan","tant","tanta","tantes","te","tene","tenim","tenir","teniu","teu",
    "teus","teva","teves","tinc","ton","tons","tot","tota","totes","tots","un","una","unes","uns",
    "us","va","vaig","vam","van","vas","veu","vosaltres","vostra","vostre","vostres","érem","éreu",
    "és","éssent","últim","ús"
};


const std::unordered_set<std::string> stopwords_en = {
    "i", "me", "my", "myself", "we", "our", "ours", "ourselves", "you", "your", "yours", "yourself", 
    "yourselves", "he", "him", "his", "himself", "she", "her", "hers", "herself", "it", "its", "itself", 
    "they", "them", "their", "theirs", "themselves", "what", "which", "who", "whom", "this", "that", 
    "these", "those", "am", "is", "are", "was", "were", "be", "been", "being", "have", "has", "had", 
    "having", "do", "does", "did", "doing", "a", "an", "the", "and", "but", "if", "or", "because", 
    "as", "until", "while", "of", "at", "by", "for", "with", "about", "against", "between", "into", 
    "through", "during", "before", "after", "above", "below", "to", "from", "up", "down", "in", "out", 
    "on", "off", "over", "under", "again", "further", "then", "once", "here", "there", "when", "where", 
    "why", "how", "all", "any", "both", "each", "few", "more", "most", "other", "some", "such", "no", 
    "nor", "not", "only", "own", "same", "so", "than", "too", "very", "s", "t", "can", "will", "just", 
    "don", "should", "now"
};


const unordered_set<string> stopwords_es = {
    "a", "acá", "ahí", "ajena", "ajeno", "ajenos", "ajenas", "al", "algo", "algún", "alguna", "algunos", 
    "algunas", "allá", "allí", "ambos", "ante", "antes", "aquel", "aquella", "aquellas", "aquellos", 
    "aquí", "arriba", "así", "atrás", "aun", "aunque", "bajo", "bastante", "bien", "cabe", "cada", "casi", 
    "cierto", "cierta", "ciertos", "ciertas", "como", "con", "conmigo", "conseguimos", "conseguir", 
    "consigo", "consigue", "consiguen", "consigues", "contigo", "contra", "cual", "cuales", 
    "cualquier", "cualquiera", "cualesquiera", "cuan", "cuando", "cuanto", "cuanta", "cuantos", "cuantas", 
    "de", "dejar", "del", "demás", "demasiada", "demasiado", "demasiadas", "demasiados", "dentro", "desde", 
    "donde", "dos", "el", "él", "ella", "ellas", "ellos", "empleáis", "emplean", "emplear", "empleas", 
    "empleo", "en", "encima", "entonces", "entre", "era", "eras", "éramos", "eran", "eres", "es", "esa", 
    "ese", "eso", "esas", "esos", "esta", "estaba", "estado", "estáis", "estamos", "están", "estar", 
    "este", "esto", "estos", "estoy", "etc", "fin", "fue", "fueron", "fui", "fuimos", "gueno", "ha", 
    "hace", "haces", "hacéis", "hacemos", "hacen", "hacer", "hacia", "hago", "hasta", "incluso", "intenta", 
    "intentas", "intentáis", "intentamos", "intentan", "intentar", "intento", "ir", "jamás", "junto", 
    "juntos", "la", "las", "lo", "los", "largo", "más", "me", "menos", "mi", "mis", "mía", "mías", 
    "mientras", "mío", "míos", "misma", "mismo", "mismas", "mismos", "modo", "mucha", "muchas", 
    "muchísimo", "muchísima", "muchísimos", "muchísimas", "mucho", "muchos", "muy", "nada", "ni", 
    "ningún", "ninguna", "ninguno", "ningunos", "ningunas", "no", "nos", "nosotras", "nosotros", 
    "nuestra", "nuestro", "nuestras", "nuestros", "nunca", "os", "otra", "otros", "otras", "para", 
    "parecer", "pero", "poca", "pocas", "podéis", "podemos", "poder", "podría", "podrías", "podríais", 
    "podríamos", "podrían", "por", "por qué", "porque", "primero", "puede", "pueden", "puedo", "pues", 
    "que", "qué", "querer", "quién", "quienes", "quienesquiera", "quienquiera", "quizá", "quizás", "sabe", 
    "sabes", "saben", "sabéis", "sabemos", "saber", "se", "según", "ser", "si", "sí", "siempre", "siendo", 
    "sin", "sino", "so", "sobre", "sois", "solamente", "solo", "sólo", "somos", "soy", "sr", "sra", 
    "sres", "sta", "su", "sus", "suya", "suyo", "suyos", "tal", "tales", "también", "tampoco", "tan", 
    "tanta", "tantas", "tanto", "tantos", "te", "tenéis", "tenemos", "tener", "tengo", "ti", "tiempo", 
    "tiene", "tienen", "toda", "todo", "todas", "todos", "tomar", "trabaja", "trabajáis", "trabajamos", 
    "trabajan", "trabajar", "trabajas", "tras", "tú", "tu", "tus", "tuya", "tuyo", "tuyos", "último", 
    "ultimo", "un", "una", "unas", "uno", "unos", "usa", "usáis", "usamos", "usan", "usar", "uso", 
    "usted", "ustedes", "va", "vais", "valor", "vamos", "varias", "varios", "vaya", "verdadera", 
    "vosotras", "vosotros", "voy", "vuestra", "vuestro", "vuestras", "vuestros", "y", "ya", "yo"
};



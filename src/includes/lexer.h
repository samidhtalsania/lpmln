typedef struct lexeme_struct {
    const char *start;
    const char *current;
    const char *begin;
} lexeme_t;

class lexer
{
public:
	static int FOL_tokenize(const char * yycursor, int len , lexeme_t* lexeme);
	static int ASP_tokenize(const char * yycursor, int len , lexeme_t* lexeme);
	static int MVSM_tokenize(const char * yycursor, int len , lexeme_t* lexeme);
};
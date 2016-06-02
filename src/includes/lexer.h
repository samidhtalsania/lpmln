typedef struct lexeme_struct {
    const char *start;
    const char *current;
} lexeme_t;

class lexer
{
public:
	static int tokenize(const char * yycursor, int len , lexeme_t* lexeme);
};
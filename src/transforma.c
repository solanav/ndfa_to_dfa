#include <math.h>

#include "../include/afnd.h"
#include "../include/afnd_plus.h"
#include "../include/transforma.h"
#include "../include/lambda_parser.h"
#include "../include/types.h"

// Creates a deterministic automata template based on a non-deterministic one
AFND *clone_tranform(AFND *afnd)
{
    int num_states = pow(2, AFNDNumEstados(afnd)); // Power set is the max
    int num_simbols = AFNDNumSimbolos(afnd); // Same as before

    AFND *afd = AFNDNuevo("af11_determinista", num_states, num_simbols);

    return afd;
}

AFND *AFNDTransforma(AFND *afnd)
{
    // Create template for deterministic transformation
    AFND *afd = clone_tranform(afnd);

    // Eliminate all lambdas
	if (lambda_parse_afnd(afnd, afd) == ERROR)
	{
		printf(P_ERROR"Lambda parser returned error\n");
		return NULL;
	}

    return afd;
}

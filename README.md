# FirstFit BestFit WorstFit NextFit in C
Simulação de gerência de memória em C, incluindo FirstFit, BestFit, WorstFit e NextFit/CircularFit

Código em C que SIMULA a gerência de memória,
Alocações dinâmicas a partir de structs definidas pelo próprio usuário que representam memórias de qualquer tamanho.
PS: É apenas uma simulação, não necessariamente é desta maneira que o algoritmo de gerência de memória realmente se comporta, como por exemplo o último struct do NextFit/CircularFit não está conectado ao primeiro struct dele para fechar o looping, apenas utilizei uma linha de comandos na inserção do CircularFit de uma forma que quando chegue ao último struct retorne ao primeiro, assim simulando um looping que de fato não existe.

------------------------------------------------------------------------------------------------------------------------------------------------------------


Memory management simulation in C, including FirstFit, BestFit, WorstFit and NextFit/CircularFit

C code that SIMULATES memory management,
Dynamic allocations from structs defined by the user that represent memories of any size.
PS: It's just a simulation, this is not necessarily the way the memory management algorithm really behaves, like for example the last struct of NextFit/CircularFit is not connected to its first struct to close the looping, I just used a line of commands in the CircularFit insertion in a way that when it reaches the last struct it returns to the first one, thus simulating a looping that does not actually exist.

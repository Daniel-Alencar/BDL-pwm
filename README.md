# Controle de servo motor através de sinal PWM

## Descrição
Este projeto tem como objetivo interagir com o periférico PWM do raspberry pi pico w, através da placa Bit Dog Lab. Para isso, foi utilizado o simulador Wokwi integrado ao VScode.

## Como Executar
1. Clone o repositório:
   ```bash
   git clone https://github.com/Daniel-Alencar/BDL-pwm
   ```
2. Navegue até o diretório do projeto:
   ```bash
   cd BDL-pwm
   ```
3. Abra o projeto no VS Code.

O projeto pode ser executado tanto no wokwi, quanto na placa Bit Dog Lab. Bastando que apenas uma constante seja alterada para identificar qual será o ambiente de execução. A constante está no arquivo principal do projeto 'pio_matrix.c'.

```c
#define USE_BITDOGLAB false
```

Por padrão, a constante vem como 'false', e o ambiente de execução deve ser o Wokwi.

### Simulador wokwi
  
4. Compile o projeto e abra o arquivo "diagram.json" para abrir o simulador wokwi.

5. Clique no botão executar e observe o programa funcionando.

6. O braço do servo motor conectado ao raspberry pi pico w deve ficar nas posições 180º, 90º e 0º, com um tempo de 5 segundos em cada posição.

7. Depois disto, o raspberry pi pico w entra em uma rotina de movimentação periódica do braço do servo motor entre os ângulos de 0 e 180 graus.

### Placa BitDogLab

Se você alterar a constante...
```c
#define USE_BITDOGLAB true
```
o ambiente de execução deve ser a placa BitDogLab.

4. Compile o projeto e passe o programa para a placa BitDogLab.

5. Ao fazer isso, você notará que as mudanças de Duty Cycle no PWM afetam a luminosidade do brilho do led azul, de forma bem análoga a posição angular do braço do servo motor (no ambiente Wokwi) 


## Vídeo de Demonstração
```bash
   Link: https://youtu.be/XKw51_FLzN8?si=BnBOmP_8aHiLCruw
```

## Adendos

Foram utilizadas as funções auxiliares compute_pwm_parameters() e compute_pwm_frequency() para o cálculo exato dos parâmetros de dividor inteiro, divisor fracionário e wrap para uma frequência desejada do PWM.

Esssas funções estão definidas no arquivo pwm/pwm.h.

## Licença
Este projeto é licenciado sob a licença MIT – consulte o arquivo LICENSE para mais detalhes.


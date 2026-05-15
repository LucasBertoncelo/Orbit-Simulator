import matplotlib
matplotlib.use('TkAgg')
import matplotlib.pyplot as plt
import matplotlib.animation as animation
import csv
import os

def animar_orbita():
    diretorio_script = os.path.dirname(os.path.abspath(__file__))
    ficheiro_csv = os.path.join(diretorio_script, 'telemetria_satelite.csv')
    
    if not os.path.exists(ficheiro_csv):
        print("Erro: Arquivo CSV nao encontrado!")
        return

    x, y = [], []
    with open(ficheiro_csv, 'r') as f:
        leitor = csv.reader(f)
        next(leitor)
        for linha in leitor:
            if len(linha) == 3:
                x.append(float(linha[1]))
                y.append(float(linha[2]))

    if len(x) == 0:
        print("Erro: O CSV está Vazio!")
        return

    fig, ax = plt.subplots(figsize=(8, 8))
    plt.style.use('dark_background')
    
    # A SOLUÇÃO ESTÁ AQUI: Trava a proporção primeiro e os limites depois!
    ax.set_aspect('equal')
    ax.set_xlim(-8000000, 8000000)
    ax.set_ylim(-8000000, 8000000)
    
    ax.scatter(0, 0, color='royalblue', s=2000, label='Terra')
    
    linha_orbita, = ax.plot([], [], color='springgreen', linewidth=1.5, alpha=0.8)
    ponto_satelite, = ax.plot([], [], 'o', color='white', markersize=6, label='Satélite')
    
    plt.title('Simulação de Órbita - Motor C + Renderização Python')
    plt.legend()

    passo = 5
    frames_totais = len(x) // passo

    def atualizar(frame):
        idx = frame * passo
        linha_orbita.set_data(x[:idx], y[:idx])
        ponto_satelite.set_data([x[idx]], [y[idx]])
        return linha_orbita, ponto_satelite

    ani = animation.FuncAnimation(fig, atualizar, frames=frames_totais, interval=10, blit=True, repeat=False)
    plt.show()

if __name__ == "__main__":
    animar_orbita()

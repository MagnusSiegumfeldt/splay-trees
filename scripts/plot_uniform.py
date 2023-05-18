import matplotlib.pyplot as plt
import pandas as pd


columns = ["Size", "Time", "Error"]
df = pd.read_csv("./logs/uniform_log.csv", header=None, names=columns)

font = {'weight' : 'bold',
        'size'   : 15}

plt.rc('font', **font)

# Compute graph
plt.rc('text', usetex=True)
plt.title("Uniform insert, access and delete")

plt.ylabel(r'Execution time [$\mu s$]')
plt.xlabel("Number of each operation")
#plt.xscale('log')


plt.errorbar(df["Size"], df["Time"], yerr=df["Error"])

plt.legend(['Splay tree'], loc='upper left')
plt.grid(True)

plt.savefig("./results/uniform.pdf", bbox_inches="tight")
#plt.show()
plt.close()

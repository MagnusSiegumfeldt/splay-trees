import matplotlib.pyplot as plt
import pandas as pd


columns = ["Size", "Time", "Error"]
df = pd.read_csv("./logs/operation_log.csv", header=None, names=columns)




# Compute graph

font = {'weight' : 'bold',
        'size'   : 15}

plt.rc('font', **font)

plt.rc('text', usetex=True)
plt.title("Execution time per operation")

plt.ylabel(r'Execution time per operation [$\mu s$]')
plt.xlabel("Number of nodes in starting splay tree")
plt.xscale('log')


plt.errorbar(df["Size"], df["Time"], yerr=df["Error"])

plt.legend(['Splay tree'], loc='upper left')
plt.grid(True)

plt.savefig("./results/operation.pdf", bbox_inches="tight")
#plt.show()
plt.close()

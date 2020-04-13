import numpy as np
import matplotlib.pyplot as plt


save_directory = "doc/figures/"

nr_threads = [1, 2, 3, 4, 5, 6, 7, 8]
mutual_links1_time = [0.016, 0.0064, 0.00477, 0.00427, 0.00461, 0.00451, 0.00417, 0.00424]
mutual_links2_time = [0.002, 0.00146, 0.00154, 0.00163, 0.00182, 0.00183, 0.00206, 0.00237]
top_n_time = [0.07, 0.0018, 0.0038, 0.0047, 0.0046, 0.0045, 0.0050, 0.0043]

fig, ax = plt.subplots() 
ax.plot(nr_threads, mutual_links1_time, label="Mutual_links1")
ax.plot(nr_threads, mutual_links2_time, label="Mutual_links2")
ax.set_xlabel("nr_threads")
ax.set_ylabel("time [ms]")

ax.grid()
ax.legend()
plt.tight_layout()
fig.savefig(save_directory + "mutuallinks.pdf", dpi=1000)

fig, ax = plt.subplots() 
ax.plot(nr_threads, top_n_time, label="top_n")
ax.set_xlabel("nr_threads")
ax.set_ylabel("time [ms]")

ax.grid()
ax.legend()
plt.tight_layout()
fig.savefig(save_directory + "top_n.pdf", dpi=1000)

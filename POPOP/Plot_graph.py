'''
    Reference : https://github.com/JunHill/Genetic_Algorithm_Learning_Projects/blob/master/Bit_Maximization/plot.py 
    Author   : JunHill
'''
import numpy as np
import matplotlib.pyplot as plt


def read_result(location, filename):
	problem_size = [10,20,40,80,160]
	values = []
	std = []
	for p_size in problem_size:
		file_name = location + filename + '_' + str(p_size) + '.txt'
		print(file_name)
		with open(file_name) as f:
			in_arr = [float(x) for x in f.read().split()]
			if in_arr[0] != -1:
				values.append(in_arr)

	values = np.array(values)
	std = np.std(values,axis=1)
	std = std.tolist()
	values = np.mean(values,axis=1)
	values = values.tolist()
	return values, std


def make_var(val1, std1, val2, std2):
	Y = [None, None]
	Yerr = [None, None]
	Y[0] = val1
	Y[1] = val2
	Yerr[0] = std1
	Yerr[1] = std2
	return Y, Yerr

def plot_result(X, Y, yerr, plot_name, y_name):
	fig, ax = plt.subplots()
	with open('./data/' + plot_name + '.txt','w') as f:
		f.write('+ Single Point Crossover:\n')
		for idx,y  in enumerate(Y[0]):
			f.write('--> Problem size {}: {}({})\n'.format(X[idx],round(y,2),round(yerr[0][idx],2)))

		f.write('+ Uniform Crossover:\n')
		for idx,y  in enumerate(Y[1]):
			f.write('--> Problem size {}: {}({})\n'.format(X[idx],round(y,2),round(yerr[1][idx],2)))




	ax.errorbar(X[:len(Y[0])], Y[0], yerr=yerr[0], fmt='-o', color='limegreen', label = 'Single Point Crossover')
	ax.errorbar(X[:len(Y[1])], Y[1], yerr=yerr[1], fmt='-o', color='crimson', label = 'Uniform Crossover')
	ax.set_title(plot_name)
	ax.set_xlabel('Problem Size')
	ax.set_ylabel(y_name)
	plt.xscale('log')
	plt.yscale('log')
	plt.xticks(X)
	ax.set_xticklabels(X)
	plt.yticks([10,100,1000,10000,100000,1000000])
	ax.set_yticks([10,100,1000,10000,100000,1000000])
	plt.legend()
	plt.savefig('./plot/{}.png'.format(plot_name))


def plot_all():

	problem_size 	= [10,20,40,80,160]
	type_fitness 	= ['OneMax','Trap5']
	type_crossover	= ['OX','UX']
	type_measure 	= ['Evaluations','MRPS']
	for t_measure in type_measure:
		dir_path = './data/{}/'.format(t_measure)
		for t_fitness in type_fitness:
			val1, std1 = read_result(dir_path,'{}_{}'.format(t_fitness,'OX'))
			val2, std2 = read_result(dir_path,'{}_{}'.format(t_fitness,'UX'))
			#print(std1)	
			Y , Yerr = make_var(val1, std1, val2, std2)
			plot_result(problem_size, Y, Yerr,t_fitness + 'Problem ({})'.format(t_measure),t_measure)

plot_all()

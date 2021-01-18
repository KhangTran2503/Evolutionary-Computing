from scipy.stats import ttest_ind

Funtions_name = ['Rastrigin','Rosenbrock']
problem_size 	= [128,256,512,1024,2048]

dir_path = './data/Run2/'
summary_ttest = './data/summary_ttest.txt'
f_summary_ttest = open(summary_ttest,"w+")

for func in Funtions_name:
    f_summary_ttest.write('{}:\n'.format(func))
    for pop_size in problem_size:
        link_Star = dir_path + 'Star/{0}_{1}.txt'.format(func, pop_size)
        link_Ring = dir_path + 'Ring/{0}_{1}.txt'.format(func, pop_size)
        # Read File 
        with open(link_Star, 'r') as f:
            lines = f.readlines()
            data_Star = []
            for line in lines:
                data_Star.append(float(line.strip().split()[-1]))

        with open(link_Ring, 'r') as f:
            lines = f.readlines()
            data_Ring = []
            for line in lines:
                data_Ring.append(float(line.strip().split()[-1]))
        
        f_summary_ttest.write('\tPop_size: {0}  p-value: {1}\n'.format(pop_size,ttest_ind(data_Star,data_Ring)[1]))

    #f_summary_ttest.close()    
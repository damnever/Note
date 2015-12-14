clean: clean-pyc

clean-pyc:
	find . -type f -name '*.pyc' -exec rm -f {} +
	find . -type f -name '*.pyo' -exec rm -f {} +
	find . -type f -name '*.~' -exec rm -f {} +
	find . -type d -name '__pycache__' -exec rm -rf {} +


clean-o:
	find . -name '*.o' -exec rm -f {} +
	find . -name '*.out' -exec rm -f {} +

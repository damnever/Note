clean: clean-pyc

clean-pyc:
	find . -name '*.pyc' -exec rm -f {} +
	find . -name '*.pyo' -exec rm -f {} +
	find . -name '*~' -exec rm -f {} +

clean-o:
	find . -name '*.o' -exec rm -f {} +
	find . -name '*.out' -exec rm -f {} +

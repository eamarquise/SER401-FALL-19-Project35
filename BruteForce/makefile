CC=g++
CFLAGS=-I.
DEPS = Project.h Student.h ClassSection.h
OBJ = BruteForce.o Project.o Student.o ClassSection.o

$(ODIR)/%.o: %.cpp $(DEPS)
	$(CC) -g -o $@ $< $(CFLAGS)

BruteForce: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)
	
.PHONY: clean

clean:
	rm -f $(ODIR)/*.o *~ core $(INCDIR)/*~
all: test-stdio.prg test-debug.prg test-mul.prg test-div.prg test-str2int.prg test-int2str.prg

%.prg: %.asm c64.inc stdio.inc debug.inc mul.inc div.inc str2int.inc int2str.inc  
	64tass --vice-labels -l $(addsuffix .mon, $(basename $@ .prg)) -L $(addsuffix .lst, $(basename $@ .prg)) -C -a -i $< -o$@
	echo "break .start\n" >> $(addsuffix .mon, $(basename $@ .prg))
	echo "break .end\n"   >> $(addsuffix .mon, $(basename $@ .prg))

%.tap: %.prg
	prg2tap $< $@

clean:
	@rm -f *.prg *.tap *.mon *.lst


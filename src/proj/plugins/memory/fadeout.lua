-- MUAN: Filtro de processamento de frames em Lua para fazer fade-out

nimages = 0   -- Numero de imagens da sequencia
count = 0     -- Contador de imagens

--// Inicializa Filtro 
--
function procfilter_init(n)
	 nimages = n
	 count = 0
	 ret = message("Fade-out Filter")
end

--// Executa Filtro (para cada frame do trecho)
--
function procfilter_exec(w,h,k)
	t = count / nimages
	count = count + 1
	mult_images(1.0 - t, 0);
	return 0;
end

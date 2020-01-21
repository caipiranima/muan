-- MUAN: Filtro de camera em Lua - motion detection

pthresh = 10   -- limiar de movimento percentual (entre 0-100) 
fmax = 500      -- numero maximo de frames capturados

duration = 1   -- duracao da imagem capturada
first = true   -- flag de inicializacao
diff = 0       -- diferenca percentual entre imagens
thresh = 0     -- limiar de movimento absoluto
fcount = 0      -- frame counter

--// Inicializa Filtro 
--
function camfilter_init(d,w,h)
	 duration = d
	 create_images(2)
	 first = 1
	 fcount = 0
	 thresh = pthresh * w * h * 3
end

--//  Executa Filtro (para cada imagem da camera)
--
function camfilter_exec(w,h)
	 if (fcount >= fmax) then
	   camfilter_off()
	   return 0
	 end
	 if (first == true) then
	   first = false
	 else
	    absdiff_images(0, 1, 2)
  	    diff = integral_image(2)
	 end
	 copy_images(0, 1)
	 if (diff > thresh) then
	    fcount = fcount + 1
	    return duration
	 else
	    return 0
	 end
end

--// Finaliza Filtro
--
function camfilter_close()
	 destroy_images()
end
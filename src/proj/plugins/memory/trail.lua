-- MUAN: Filtro de processamento de frames em Lua para fazer rastro

first = true
t = 0.5

--// Inicializa Filtro 
--
function procfilter_init(n)
	 create_images(1)
end

--// Executa Filtro (para cada frame do trecho)
--
function procfilter_exec(w,h,k)
	 if (first) then
	    first = false
	    copy_images(0, 1)
	    return 0
	 end
	 mult_images(t, 0)
	 mult_images(1.0 - t, 1)
	 add_images(1, 0, 0)
	 copy_images(0, 1)
	 return 0;     
end

--// Finaliza Filtro 
--
function procfilter_close()
	 destroy_images()
end

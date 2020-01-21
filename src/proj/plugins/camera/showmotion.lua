-- MUAN: Filtro de camera em Lua - motion detection

first = true   -- flag de inicializacao

--// Inicializa Filtro 
--
function camfilter_init(d,w,h)
	 duration = d
	 create_images(2)
	 first = 1
end

--//  Executa Filtro (para cada imagem da camera)
--
function camfilter_exec(w,h)
	 if (first == true) then
	   first = false
	 else
	   absdiff_images(0, 1, 2)
	   copy_images(0, 1)
	   copy_images(2, 0) -- or, add_images(2, 0)
	 end
	 return 0
end

--// Finaliza Filtro
--
function camfilter_close()
	 destroy_images()
end
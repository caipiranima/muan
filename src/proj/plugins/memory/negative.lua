-- MUAN: Filtro de processamento de frames em Lua para fazer imagens em negativo

dofast = true -- processamento rapido (em C++)
nimages = 0    -- Numero de imagens da sequencia

--// Inicializa Filtro 
--
function procfilter_init(n,w,h)
	 nimages = n
end

--// Executa Filtro (para cada frame do trecho)
--
function procfilter_exec(w,h,k)
	 if (dofast) then
	   negative()
	 else
	   for u=0,w-1 do
	       for v=0,h-1 do
		  local r,g,b=getpixel(u,v)
		  putpixel(u,v, 255-r,255-g,255-b)
	  	end
	    end
	end
	return 0;
end

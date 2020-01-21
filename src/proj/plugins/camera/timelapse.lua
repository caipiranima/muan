-- MUAN: Filtro de camera em Lua para captura "timelapse" de imagens

duration = 1   -- Duracao do frame capturado  
interval = 30  -- Intervalo de tempo na captura
skipped = 0    -- variavel auxiliar de controle


--// Inicializa Filtro 
--
function camfilter_init(d)
	duration = d
	skipped = interval
	beep()
end

--// Executa Filtro (para cada imagem da camera)
--
function camfilter_exec(w,h)
	skipped = skipped - 1
	if (skipped <= 0) then
	  skipped = interval
	  beep()
	  return duration
	else
	  return 0
	end
end

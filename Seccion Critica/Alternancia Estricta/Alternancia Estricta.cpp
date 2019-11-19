int turno_proceso; //1 proceso 1, 2 proceso 2
Proceso1()
{
	while (true)
	{
		[REALIZA_TAREAS_INICIALES]
		while (turno_proceso == 2) {}
		[SECCION_CRITICA]
		turno_proceso = 2;
		[REALIZA_TAREAS_FINALES]
	}
}

Proceso2()
{
	while (true)
	{
		[REALIZA_TAREAS_INICIALES]
		while (turno_proceso == 1) {}
		[SECCION_CRITICA]
		turno_proceso = 1;
		[REALIZA_TAREAS_FINALES]
	}
}

iniciar() {
	turno_proceso = 1;
	Proceso1();
	Proceso2();
}
#implementacion DOS_ATTACK
#By leo
#code python > 2

def dos_attack(ips):
    """ devuelve una lista con los ips que realizaron un atake dos

        pre: ips es un diccionario con key = ip, valor = estructura {direccion,tiempo,metodo,recurso}
        post: devueve una lista de ips = strings
    """

    dos_dic = {}
    dos_ip = []

    #interador (->c implements)
    #hay que eliminarlo cuando terminemos la implementacion
    for ip in ips:

        if ip.direccion in dos_dic:
            tiempo = ip.tiempo

            if apariciones(tiempo, dos_dic[ip.direccion]) >= 5:
                lista_tiempos.append(tiempo);

                if ip.direccion not in dos_ip:
                    dos_ip.append(ip.direccion)

            else:
                #limpio los registros ya que los tiempos estan ordenados
                dos_dic[ip.direccion] = []

    #ya recorri todos los import ips
    #elimino DOS_DIC ( -> C )
    #elimino ITERADOR IPS ( -> C)
    return dos_ip

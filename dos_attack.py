#implementacion DOS_ATTACK
#By leo
#code python > 2

def dos_attack(ips):
    """ devuelve una lista con los ips que realizaron un atake dos

        pre: ips es un diccionario con key = ip, valor = [] que contiene [estructura] {direccion,tiempo,metodo,recurso}
        post: devueve una lista de ips = strings
    """

    dos_dic = {}
    dos_ip = []

    #interador (->c implements)
    #hay que eliminarlo cuando terminemos la implementacion
    for ip_key in ips:

        #iterador lista
        for ip in ips[ip_key]:

            #no pertenece hash o !hash(key)
            if ip.direccion not in dos_dic or dos_dic[ip.direccion] = []:
                dos_dic[ip.direccion] = [ip]
                continue

            dos_time_ultimo = dos_dic[ip.direccion][-1]

            #no hay DOS
            if dos_time_ultimo != ip.tiempo:
                #limpio el registro
                dos_dic[ip.direccion] = [];

            else:
                #agrego al registro
                dos_dic[ip.direccion].append(ip.tiempo)

                #pregunto si el largo de la lista es mayor o igual 5
                #en caso afirmativo tenemos un atake DOS
                if len(dos_dic[ip.direccion]) >= 5:

                    #verificamos si el IP esta en la BLACK LIST
                    #si no esta la agregamos
                    #en caso contrario no hacemos nada para evitar duplicados 
                    if ip.direccion not in dos_ip:
                        dos_ip.append(ip.direccion)



    #ya recorri todos los import ips
    #elimino DOS_DIC ( -> C )
    #elimino ITERADOR IPS ( -> C)
    #elimino ITERADOR LISTA_IPS ( -> C)
    return dos_ip

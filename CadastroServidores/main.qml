import QtQuick 2.14
import QtQuick.Window 2.14
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.4
import QtQuick.Dialogs 1.3
import meuCSV 1.0

ApplicationWindow {
    id: rootId
    width: 1080
    height: 720
    visible: true
    title: qsTr("Cadastro de Servidores")
    property int linhaSelecionada
    property string mensagem

    ClasseCSV {
        id: controleCSV
        arquivo: txtId.text
        onError: {
            mensagem = msg
            erroDialogId.open()
        }
        onSucesso: {
            mensagem = msg
            erroDialogId.open()
        }
    }

    header: ToolBar {
        height: rootId.height * 0.1

        background: Rectangle {
            color: "#636363"
        }

        RowLayout {
            spacing: 20
            anchors.verticalCenter: parent.verticalCenter
            anchors.fill: parent

            CheckBox {
                Layout.leftMargin: 20
                id: testeConnId
                text: " Teste de \n Conectividade"
                font.bold: true
            }

            TextField {
                id: txtId
                Layout.fillHeight: true
                Layout.fillWidth: true
                Layout.maximumHeight: parent.height - 20
                Layout.maximumWidth: 700
                placeholderText: "Selecione o diretório para o arquivo a ser criado."
                selectByMouse: true
            }

            Button {
                text: "Selecionar"
                Layout.maximumHeight: 35
                Layout.maximumWidth: 150
                Layout.fillHeight: true
                Layout.fillWidth: true
                onClicked: {
                    fileDialogId.open()
                }
            }

            TextField {
                id: nomeArquivoId
                Layout.fillHeight: true
                Layout.fillWidth: true
                Layout.maximumHeight: parent.height - 20
                Layout.maximumWidth: 150
                Layout.rightMargin: 20
                placeholderText: "Nome do arquivo."
                selectByMouse: true
            }

        }
    }

    Rectangle {
        id: backgroundId
        color: "#636363"
        anchors.fill: parent

        GridLayout {
            id: mGridLayoutId
            anchors.fill: parent
            columns: 2
            layoutDirection: Qt.LeftToRight

            Rectangle{
                id: regiao2Id
                Layout.maximumWidth: 210
                Layout.fillHeight: true
                Layout.fillWidth: true
                color: "#636363"
                radius: 5
                ColumnLayout{
                    anchors.fill: parent
                    Layout.maximumHeight: parent.height - 10
                    spacing: 10

                    RoundButton {
                        text: "Novo"
                        font.pointSize: 18
                        radius: 10
                        Layout.fillWidth: true
                        Layout.maximumWidth: regiao2Id.width - 20
                        height: 50
                        Layout.alignment: Qt.AlignHCenter
                        palette {
                            button: "orange"
                        }
                        onClicked: {
                            novoDialogId.open()
                        }
                    }
                    RoundButton {
                        text: "Editar"
                        font.pointSize: 20
                        radius: 12
                        Layout.fillWidth: true
                        Layout.maximumWidth: regiao2Id.width - 20
                        height: 50
                        Layout.alignment: Qt.AlignHCenter
                        palette {
                            button: "orange"
                        }
                        onClicked: {
                            if(linhaSelecionada === 0) {
                                selecioneDialogId.open()
                            } else {
                                editDialogId.open()
                            }
                        }
                    }
                    RoundButton {
                        text: "Remover"
                        font.pointSize: 20
                        radius: 12
                        Layout.fillWidth: true
                        Layout.maximumWidth: regiao2Id.width - 20
                        height: 50
                        Layout.alignment: Qt.AlignHCenter
                        palette {
                            button: "orange"
                        }
                        onClicked: {
                            if(linhaSelecionada === 0) {
                                selecioneDialogId.open()
                            } else {
                                removerDialogId.open()
                            }
                        }
                    }
                    RoundButton {
                        text: "Salvar"
                        font.pointSize: 20
                        radius: 12
                        Layout.fillWidth: true
                        Layout.maximumWidth: regiao2Id.width - 20
                        height: 50
                        Layout.alignment: Qt.AlignHCenter
                        palette {
                            button: "orange"
                        }
                        onClicked: {
                            //Converter Model para dados pré-csv
                            var precsv = ""
                            for(var i=1;i < modelId.count;i++){
                                precsv+= modelId.get(i).nome +","+modelId.get(i).endereco +","+modelId.get(i).porta +","+modelId.get(i).tipo +"$$$"
                            }
                            controleCSV.salvarCSV(precsv,nomeArquivoId.text)
                        }
                    }

                    RoundButton {
                        text: "Carregar"
                        font.pointSize: 20
                        radius: 12
                        Layout.fillWidth: true
                        Layout.maximumWidth: regiao2Id.width - 20
                        height: 50
                        Layout.alignment: Qt.AlignHCenter
                        palette {
                            button: "orange"
                        }
                        onClicked: {
                            //Carrega model
                            carregarFileDialogId.open()

                        }
                    }

                }
            }

            Rectangle{
                id: regiao3Id
                border.color: "#343434"
                border.width: 1
                Layout.fillHeight: true
                Layout.fillWidth: true

                TableView{
                    id: tabelaId
                    anchors.fill: parent
                    model: modelId

                    delegate:RowLayout{
                        id: linhaId
                        spacing: 0
                        Rectangle {
                            implicitWidth: regiao3Id.width * 0.3
                            implicitHeight: 50
                            border.width: 1
                            color:nome === "Nome"?"#878787":"white"
                            Text {
                                text: nome
                                color: "black"
                                font.bold: nome === "Nome"?true:false
                                font.pointSize: 16
                                anchors.centerIn: parent
                            }
                        }
                        Rectangle {
                            implicitWidth: regiao3Id.width* 0.4
                            implicitHeight: 50
                            border.width: 1
                            color:endereco === "Endereço"?"#878787":"white"
                            Text {
                                text: endereco
                                color: "black"
                                font.bold: endereco === "Endereço"?true:false
                                font.pointSize: 16
                                anchors.centerIn: parent
                            }

                        }
                        Rectangle {
                            implicitWidth: regiao3Id.width * 0.2
                            implicitHeight: 50
                            border.width: 1
                            color:porta === "Porta"?"#878787":"white"
                            Text {
                                text: porta
                                color: "black"
                                font.bold: porta === "Porta"?true:false
                                font.pointSize: 16
                                anchors.centerIn: parent
                            }

                        }
                        Rectangle {
                            implicitWidth: regiao3Id.width * 0.1
                            implicitHeight: 50
                            border.width: 1
                            color:tipo === "Tipo"?"#878787":"white"
                            Text {
                                text: tipo
                                color: "black"
                                font.bold: tipo === "Tipo"?true:false
                                font.pointSize: 16
                                anchors.centerIn: parent
                            }

                        }
                        MouseArea {
                            // anchors.fill: parent
                            width: parent.width
                            height: parent.height
                            onClicked: {
                                linhaSelecionada = index

                            }
                        }

                    }
                }
            }

        }
    }

    footer: ToolBar {
        height: rootId.height * 0.1
        background: Rectangle {
            color: "#636363"
        }

        RowLayout {
            spacing: 10
            anchors.verticalCenter: parent.verticalCenter
            anchors.fill: parent

            Label {
                text: "Servidor Selecionado: "
                Layout.leftMargin: 20
                font.bold: true
                font.pointSize: 16
            }
            Label {
                text: linhaSelecionada === 0?"Nenhum servidor selecionado":modelId.get(linhaSelecionada).nome + " - "+ modelId.get(linhaSelecionada).endereco + ":" + modelId.get(linhaSelecionada).porta + " - " + modelId.get(linhaSelecionada).tipo
                color: "white"
                font.pointSize: 16
            }
        }
    }

    Dialog {
        id: novoDialogId
        title: "Novo Servidor"
        standardButtons: Dialog.Ok | Dialog.Cancel

        ColumnLayout {
            spacing: 20
            anchors.fill: parent
            Label {
                elide: Label.ElideRight
                text: "Insira os dados do novo servidor:"
                font.pointSize: 14
                Layout.fillWidth: true
            }
            TextField {
                id: novoNomeId
                focus: true
                placeholderText: "Nome"
                Layout.fillWidth: true
            }
            TextField {
                id: novoEnderecoId
                placeholderText: "Endereço"
                Layout.fillWidth: true
            }
            TextField {
                id: novoPortaId
                placeholderText: "Porta"
                Layout.fillWidth: true
            }
            ComboBox {
                id: novoTipoId
                textRole: "text"
                Layout.fillWidth: true
                model: ListModel {
                    ListElement{ text:"PACS";}
                    ListElement{ text:"MWL";}
                    ListElement{ text:"PRT";}
                }
                Layout.bottomMargin: 10
                Layout.alignment: Qt.AlignHCenter
            }
        }

        onAccepted: { //Incluir na lista
            modelId.append({nome: novoNomeId.text, endereco: novoEnderecoId.text, porta: novoPortaId.text, tipo: novoTipoId.currentText })
            novoNomeId.clear();novoEnderecoId.clear();novoPortaId.clear();
        }

    }

    Dialog {
        id: editDialogId
        title: "Editar Servidor"
        standardButtons: Dialog.Ok | Dialog.Cancel

        ColumnLayout {
            spacing: 20
            anchors.fill: parent
            Label {
                elide: Label.ElideRight
                text: "Insira os dados do novo servidor:"
                font.pointSize: 14
                Layout.fillWidth: true
            }
            TextField {
                id: editNomeId
                focus: true
                text: modelId.get(linhaSelecionada).nome
                Layout.fillWidth: true
            }
            TextField {
                id: editEnderecoId
                text: modelId.get(linhaSelecionada).endereco
                Layout.fillWidth: true
            }
            TextField {
                id: editPortaId
                text: modelId.get(linhaSelecionada).porta
                Layout.fillWidth: true
            }
            ComboBox {
                id: editTipoId
                textRole: "text"
                Layout.fillWidth: true
                model: ListModel {
                    ListElement{ text:"PACS";}
                    ListElement{ text:"MWL";}
                    ListElement{ text:"PRT";}
                }
                Layout.bottomMargin: 10
                Layout.alignment: Qt.AlignHCenter
            }
        }

        onAccepted: { //Alterar na lista
            modelId.set(linhaSelecionada,{nome: editNomeId.text, endereco: editEnderecoId.text, porta: editPortaId.text, tipo: editTipoId.currentText })
            editNomeId.clear();editEnderecoId.clear();editPortaId.clear();
        }

    }

    FileDialog{
        id:carregarFileDialogId
        title:"Escolha o Arquivo"
        selectFolder: false
        selectMultiple: false

        onAccepted: {
            //Converte caminho
            var caminho = carregarFileDialogId.fileUrl.toString();
            caminho = caminho.replace(/^(file:\/{3})/,"");
            caminho = decodeURIComponent(caminho);
            //Prepara model
            modelId.clear()
            modelId.append({nome: "Nome", endereco: "Endereço", porta: "Porta", tipo: "Tipo" })
            //Carrega csv e insere no model
            var carregarCSV = controleCSV.abrirCSV(caminho)
            var linhas = carregarCSV.split('$$$')
            for(var i=0;i < linhas.length-1;i++){
                var celulas = linhas[i].split(',')
                modelId.append({nome: celulas[0], endereco: celulas[1], porta: celulas[2], tipo: celulas[3] })
            }

        }

    }

    FileDialog{
        id:fileDialogId
        title:"Escolha o Arquivo"
        selectFolder: true
        selectMultiple: false

        onAccepted: {
            //Converte caminho
            var caminho = fileDialogId.fileUrl.toString();
            caminho = caminho.replace(/^(file:\/{3})/,"");
            caminho = decodeURIComponent(caminho);
            txtId.text = caminho
            controleCSV.setArquivo(caminho)

        }
    }

    MessageDialog{
        id: removerDialogId
        title: "Apagar servidor"
        text: "Deseja remover o servidor selecionado? Essa ação não pode ser desfeita."
        standardButtons: StandardButton.Yes | StandardButton.No
        onYes: {
            modelId.remove(linhaSelecionada)
            linhaSelecionada = 0
        }
    }

    MessageDialog{
        id: selecioneDialogId
        title: "Selecione um servidor"
        text: "Para prosseguir, é necessário selecionar um servidor."
        standardButtons: StandardButton.Ok
    }

    MessageDialog{
        id: erroDialogId
        title: " "
        text: mensagem
        standardButtons: StandardButton.Ok
    }

    ListModel {
        id: modelId

        ListElement {
            nome: "Nome"; endereco: "Endereço"; porta: "Porta"; tipo: "Tipo"
        }

    }

}

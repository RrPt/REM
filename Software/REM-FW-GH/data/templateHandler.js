class TemplateHandler{
	
	constructor(templateId){
		this.template = $(templateId);
		this.templateContent =  $(this.template).prop('content');
		
	}
	
	setTemplateField(fieldId,content){
		let field = $(this.templateContent).find(fieldId);
		$(field).text(content);
		}

	setTemplateAttr(fieldId,AttrName,content){
		let field = $(this.templateContent).find(fieldId);
		$(field).attr(AttrName,content);
		}
		
	getTemplate(){
		return this.template;
		}
	
	
}
	